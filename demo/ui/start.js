"use strict";

const electron = require("electron");
const app = electron.app;

let mainWindow = undefined;

var shouldQuit = app.makeSingleInstance(function(commandLine, workingDirectory) {
  if (mainWindow !== undefined) {
    if (mainWindow.isMinimized()) mainWindow.restore();
    mainWindow.focus();
  }
});

if (shouldQuit) {
  app.quit();
  return;
}

app.on("window-all-closed", function() {
  if (process.platform !== "darwin") {
    app.quit();
  }
});

app.on("ready", function() {
  mainWindow = new electron.BrowserWindow({
    title: "UI Demo",
    icon: "ui_icon.png",
    webPreferences: { nodeIntegration: false }
  });
  mainWindow.maximize();
  mainWindow.setMenu(null);
  mainWindow.on("closed", function() {
    mainWindow = null;
  });
  mainWindow.loadURL(`file://${__dirname}/index.html`);
});
