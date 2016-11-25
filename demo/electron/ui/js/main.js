"use strict";

function $(element) {
  return document.querySelector(element);
}

function get_by_attr(element, attr) {
  var i;
  var result;
  var nodes = element.childNodes;
  for (i = 0; i < nodes.length; i += 1) {
    if (nodes[i].hasAttribute !== undefined) {
      if (nodes[i].hasAttribute(attr)) {
        return nodes[i];
      } else {
        result = get_by_attr(nodes[i], attr);
        if (result !== undefined) {
          return result;
        }
      }
    }
  }
  return undefined;
}

function make_box(header, body, footer) {
  var div = document.createElement("div");
  div.className = "box";
  div.innerHTML = '<div class="header">' + header + '</div>';
  div.innerHTML += '<div class="body">' + body + '</div>';
  div.innerHTML += '<div class="footer">' + footer + '</div>';
  $("#grid").appendChild(div);
  return div;
}

function make_simple_box(header, footer) {
  return make_box(header, "<span data-value>&nbsp;</span>", footer);
}

function make_smart_box(header, footer) {
  return make_box(header, "<pre data-value></pre>", "");
}

function make_effect_box(effect_list) {
  var options = "";
  effect_list.forEach(function (e, i) {
    options += '<option value="' + i + '">' + e + '</option>';
  });
  return make_box("Effect list", "<select data-select>" + options + "</select>", "");
}

function main() {
  function make_list(hw, to_dict, title, name, units) {
    var dict = to_dict(hw);
    for (var key in dict) {
      (function (box, key) {
        updaters.push(function (hw) {
          get_by_attr(box, "data-value").textContent = to_dict(hw)[key] + " " + units;
        });
      })(make_simple_box(key, name), key);
    }
  }

  function add_mbs(hw) {
    hw.mbs.forEach(function (v, i) {
      var j = i;
      make_list(hw, function (hw) { return hw.mbs[j].fan; }, "MB" + i + " Fan", v.name, "RPM");
      make_list(hw, function (hw) { return hw.mbs[j].temp; }, "MB" + i + " Temp", v.name, "C");
    });
  }

  function add_cpus(hw) {
    hw.cpus.forEach(function (v, i) {
      var j = i;
      make_list(hw, function (hw) { return hw.cpus[j].load; }, "CPU" + i + " Load", v.name, "%");
      make_list(hw, function (hw) { return hw.cpus[j].temp; }, "CPU" + i + " Temp", v.name, "C");
    });
  }

  function add_hdds(hw) {
    hw.hdds.forEach(function (v, i) {
      var j = i;
      make_list(hw, function (hw) { return hw.hdds[j].temp; }, "HDD" + i + " Temp", v.name, "C");
    });
  }

  function add_gpus(hw) {
    hw.gpus.forEach(function (v, i) {
      var j = i;
      make_list(hw, function (hw) { return hw.gpus[j].fan; }, "GPU" + i + " Fan", v.name, "RPM");
      make_list(hw, function (hw) { return hw.gpus[j].load; }, "GPU" + i + " Load", v.name, "%");
      make_list(hw, function (hw) { return hw.gpus[j].temp; }, "GPU" + i + " Temp", v.name, "C");
    });
  }

  function add_smart_list(smart_list) {
    var box;
    var data;
    smart_list.forEach(function (v, i) {
      box = make_smart_box("HDD" + i + " S.M.A.R.T.", v.name);
      get_by_attr(box, "data-value").textContent = "";
      for (var key in v.attributes) {
        get_by_attr(box, "data-value").textContent += v.attributes[key].name + ": " + v.attributes[key].value + "\n";
      }
    });
  }

  function add_effects() {
    var effect_list = ["none", "monitor"];
    var box = make_effect_box(effect_list);
    var select = get_by_attr(box, "data-select");
    select.addEventListener("change", function (e) {
      client_data.effect = effect_list[select.selectedIndex];
      jbog.send_message("set_client_data", client_data);
    });
  }

  function create_widgets(hw) {
    updaters = [];
    $("#grid").innerHTML = "";
    add_effects();
    add_mbs(hw);
    add_cpus(hw);
    add_hdds(hw);
    add_gpus(hw);
    update_widgets(hw);
  }

  function update_widgets(hw) {
    updaters.forEach(function (e) {
      e(hw);
    });
  }

  var updaters;
  var client_data;

  var jbog = jbog_client.make();

  jbog.on("client_data", function (data) {
    if (client_data === undefined) {
      client_data = data;
    } else {
      jbog.send_message("set_client_data", client_data);
    }
    jbog.repeat_message("get_hardware_data");
    jbog.send_message("get_smart_data");
    jbog.on("hardware_data", function (hw) {
      create_widgets(hw);
      jbog.on("hardware_data", update_widgets);
    });
  });

  jbog.on("smart_data", add_smart_list);

  jbog.run("127.0.0.1", 8000);
}

main();
