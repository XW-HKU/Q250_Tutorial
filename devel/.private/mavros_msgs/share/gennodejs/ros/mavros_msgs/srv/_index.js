
"use strict";

let LogRequestEnd = require('./LogRequestEnd.js')
let WaypointPull = require('./WaypointPull.js')
let StreamRate = require('./StreamRate.js')
let SetMavFrame = require('./SetMavFrame.js')
let WaypointClear = require('./WaypointClear.js')
let FileRemoveDir = require('./FileRemoveDir.js')
let SetMode = require('./SetMode.js')
let CommandTriggerControl = require('./CommandTriggerControl.js')
let WaypointPush = require('./WaypointPush.js')
let WaypointSetCurrent = require('./WaypointSetCurrent.js')
let CommandHome = require('./CommandHome.js')
let FileOpen = require('./FileOpen.js')
let FileRemove = require('./FileRemove.js')
let LogRequestData = require('./LogRequestData.js')
let FileList = require('./FileList.js')
let FileClose = require('./FileClose.js')
let FileChecksum = require('./FileChecksum.js')
let CommandBool = require('./CommandBool.js')
let CommandLong = require('./CommandLong.js')
let VehicleInfoGet = require('./VehicleInfoGet.js')
let CommandInt = require('./CommandInt.js')
let ParamGet = require('./ParamGet.js')
let FileWrite = require('./FileWrite.js')
let FileRead = require('./FileRead.js')
let ParamPush = require('./ParamPush.js')
let ParamPull = require('./ParamPull.js')
let FileMakeDir = require('./FileMakeDir.js')
let ParamSet = require('./ParamSet.js')
let CommandTOL = require('./CommandTOL.js')
let MessageInterval = require('./MessageInterval.js')
let FileRename = require('./FileRename.js')
let CommandTriggerInterval = require('./CommandTriggerInterval.js')
let LogRequestList = require('./LogRequestList.js')
let FileTruncate = require('./FileTruncate.js')

module.exports = {
  LogRequestEnd: LogRequestEnd,
  WaypointPull: WaypointPull,
  StreamRate: StreamRate,
  SetMavFrame: SetMavFrame,
  WaypointClear: WaypointClear,
  FileRemoveDir: FileRemoveDir,
  SetMode: SetMode,
  CommandTriggerControl: CommandTriggerControl,
  WaypointPush: WaypointPush,
  WaypointSetCurrent: WaypointSetCurrent,
  CommandHome: CommandHome,
  FileOpen: FileOpen,
  FileRemove: FileRemove,
  LogRequestData: LogRequestData,
  FileList: FileList,
  FileClose: FileClose,
  FileChecksum: FileChecksum,
  CommandBool: CommandBool,
  CommandLong: CommandLong,
  VehicleInfoGet: VehicleInfoGet,
  CommandInt: CommandInt,
  ParamGet: ParamGet,
  FileWrite: FileWrite,
  FileRead: FileRead,
  ParamPush: ParamPush,
  ParamPull: ParamPull,
  FileMakeDir: FileMakeDir,
  ParamSet: ParamSet,
  CommandTOL: CommandTOL,
  MessageInterval: MessageInterval,
  FileRename: FileRename,
  CommandTriggerInterval: CommandTriggerInterval,
  LogRequestList: LogRequestList,
  FileTruncate: FileTruncate,
};
