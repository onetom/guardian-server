// Author: Peter Sovietov

"use strict";

var jbog_client = {};

jbog_client.ws = (function () {
  var def = {};

  def.OPEN = 1;
  def.CLOSED = 3;

  def.connect = function (host, port) {
    this.socket = new WebSocket("ws://" + host + ":" + port);
    this.socket.onopen = this.onopen;
    this.socket.onmessage = this.onmessage;
    this.socket.onclose = this.onclose;
    this.socket.onerror = this.onclose;
  };

  def.is_connected = function () {
    return this.socket !== undefined && this.socket.readyState === jbog_client.ws.OPEN;
  };

  def.is_disconnected = function () {
    return this.socket === undefined || this.socket.readyState === jbog_client.ws.CLOSED;
  };

  def.send = function (data) {
    if (this.is_connected()) {
      this.socket.send(data);
    }
  };

  def.close = function () {
    if (this.socket !== undefined) {
      this.socket.close();
    }
  };

  def.make = function (open, message, close) {
    var self = Object.create(this);
    self.socket = undefined;
    self.onopen = open;
    self.onmessage = function (e) {
      message(e.data);
    };
    self.onclose = close;
    return self;
  };

  return def;
})();

var jbog_client = (function () {
  var def = jbog_client;

  def.send_message = function (tag, data) {
    this.ws.send(JSON.stringify({
      "tag": tag,
      "data": data
    }));
  };

  def.repeat_message = function (tag, data) {
    this.send_message(tag, data);
    this.repeaters[tag] = data;
  };

  def.update = function () {
    var self = this;
    if (this.ws.is_disconnected()) {
      this.ws.connect(this.host, this.port);
    } else {
      Object.keys(this.repeaters).forEach(function (e) {
        self.send_message(e, self.repeaters[e]);
      });
    }
  };

  def.run = function (host, port) {
    this.host = host;
    this.port = port;
    this.ws.connect(this.host, this.port);
    setInterval(this.update.bind(this), this.update_interval);
  };

  def.handle_message = function (tag, data) {
    if (this.handlers[tag] !== undefined) {
      this.handlers[tag](data);
    }
  };

  def.on_open = function () {
    this.handle_message("open");
  };

  def.on_message = function (data) {
    var message = JSON.parse(data);
    this.handle_message(message.tag, message.data);
  };

  def.on_close = function () {
    this.handle_message("close");
  };

  def.on = function (tag, f) {
    this.handlers[tag] = f;
  };

  def.make = function () {
    var self = Object.create(this);
    self.host = undefined;
    self.port = undefined;
    self.update_interval = 1000;
    self.repeaters = {};
    self.handlers = {};
    self.ws = jbog_client.ws.make(
      self.on_open.bind(self),
      self.on_message.bind(self),
      self.on_close.bind(self)
    );
    return self;
  };

  return def;
})();
