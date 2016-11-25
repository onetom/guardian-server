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
  function make_list(hw, to_list, title, name, units) {
    to_list(hw).forEach(function (v, i) {
      var box = make_simple_box(title + i, name);
      var j = i;
      updaters.push(function (hw) {
        get_by_attr(box, "data-value").textContent = to_list(hw)[j] + " " + units;
      });
    });
  }

  function add_mb_list(hw) {
    hw.mb_list.forEach(function (v, i) {
      var j = i;
      make_list(hw, function (hw) { return hw.mb_list[j].fan_list; }, "MB" + i + " Fan", v.name, "RPM");
      make_list(hw, function (hw) { return hw.mb_list[j].temp_list; }, "MB" + i + " Temp", v.name, "C");
    });
  }

  function add_cpu_list(hw) {
    hw.cpu_list.forEach(function (v, i) {
      var j = i;
      make_list(hw, function (hw) { return hw.cpu_list[j].load_list; }, "CPU" + i + " Load", v.name, "%");
      make_list(hw, function (hw) { return hw.cpu_list[j].temp_list; }, "CPU" + i + " Temp", v.name, "C");
    });
  }

  function add_hdd_list(hw) {
    hw.hdd_list.forEach(function (v, i) {
      var j = i;
      make_list(hw, function (hw) { return hw.hdd_list[j].temp_list; }, "HDD" + i + " Temp", v.name, "C");
    });
  }

  function add_gpu_list(hw) {
    hw.gpu_list.forEach(function (v, i) {
      var j = i;
      make_list(hw, function (hw) { return hw.gpu_list[j].fan_list; }, "GPU" + i + " Fan", v.name, "RPM");
      make_list(hw, function (hw) { return hw.gpu_list[j].load_list; }, "GPU" + i + " Load", v.name, "%");
      make_list(hw, function (hw) { return hw.gpu_list[j].temp_list; }, "GPU" + i + " Temp", v.name, "C");
    });
  }

  function add_smart_list(smart_list) {
    var box;
    var data;
    smart_list.forEach(function (v, i) {
      box = make_smart_box("HDD" + i + " S.M.A.R.T.", v.name);
      data = "";
      v.attr_list.forEach(function (v) {
        data += v.toString() + "\n"
      });
      get_by_attr(box, "data-value").textContent = data;
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
    add_mb_list(hw);
    add_cpu_list(hw);
    add_hdd_list(hw);
    add_gpu_list(hw);
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
