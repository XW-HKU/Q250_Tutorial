
"use strict";

let CompanionProcessStatus = require('./CompanionProcessStatus.js');
let CamIMUStamp = require('./CamIMUStamp.js');
let AttitudeTarget = require('./AttitudeTarget.js');
let WheelOdomStamped = require('./WheelOdomStamped.js');
let Altitude = require('./Altitude.js');
let RCIn = require('./RCIn.js');
let Param = require('./Param.js');
let HilStateQuaternion = require('./HilStateQuaternion.js');
let DebugValue = require('./DebugValue.js');
let CommandCode = require('./CommandCode.js');
let LogEntry = require('./LogEntry.js');
let ADSBVehicle = require('./ADSBVehicle.js');
let Mavlink = require('./Mavlink.js');
let HilActuatorControls = require('./HilActuatorControls.js');
let Thrust = require('./Thrust.js');
let ActuatorControl = require('./ActuatorControl.js');
let HilGPS = require('./HilGPS.js');
let StatusText = require('./StatusText.js');
let Trajectory = require('./Trajectory.js');
let Waypoint = require('./Waypoint.js');
let HilSensor = require('./HilSensor.js');
let PositionTarget = require('./PositionTarget.js');
let ParamValue = require('./ParamValue.js');
let ManualControl = require('./ManualControl.js');
let OverrideRCIn = require('./OverrideRCIn.js');
let BatteryStatus = require('./BatteryStatus.js');
let ExtendedState = require('./ExtendedState.js');
let RTCM = require('./RTCM.js');
let RCOut = require('./RCOut.js');
let OpticalFlowRad = require('./OpticalFlowRad.js');
let TimesyncStatus = require('./TimesyncStatus.js');
let State = require('./State.js');
let WaypointList = require('./WaypointList.js');
let Vibration = require('./Vibration.js');
let HomePosition = require('./HomePosition.js');
let HilControls = require('./HilControls.js');
let FileEntry = require('./FileEntry.js');
let VehicleInfo = require('./VehicleInfo.js');
let VFR_HUD = require('./VFR_HUD.js');
let RadioStatus = require('./RadioStatus.js');
let WaypointReached = require('./WaypointReached.js');
let LogData = require('./LogData.js');
let GlobalPositionTarget = require('./GlobalPositionTarget.js');

module.exports = {
  CompanionProcessStatus: CompanionProcessStatus,
  CamIMUStamp: CamIMUStamp,
  AttitudeTarget: AttitudeTarget,
  WheelOdomStamped: WheelOdomStamped,
  Altitude: Altitude,
  RCIn: RCIn,
  Param: Param,
  HilStateQuaternion: HilStateQuaternion,
  DebugValue: DebugValue,
  CommandCode: CommandCode,
  LogEntry: LogEntry,
  ADSBVehicle: ADSBVehicle,
  Mavlink: Mavlink,
  HilActuatorControls: HilActuatorControls,
  Thrust: Thrust,
  ActuatorControl: ActuatorControl,
  HilGPS: HilGPS,
  StatusText: StatusText,
  Trajectory: Trajectory,
  Waypoint: Waypoint,
  HilSensor: HilSensor,
  PositionTarget: PositionTarget,
  ParamValue: ParamValue,
  ManualControl: ManualControl,
  OverrideRCIn: OverrideRCIn,
  BatteryStatus: BatteryStatus,
  ExtendedState: ExtendedState,
  RTCM: RTCM,
  RCOut: RCOut,
  OpticalFlowRad: OpticalFlowRad,
  TimesyncStatus: TimesyncStatus,
  State: State,
  WaypointList: WaypointList,
  Vibration: Vibration,
  HomePosition: HomePosition,
  HilControls: HilControls,
  FileEntry: FileEntry,
  VehicleInfo: VehicleInfo,
  VFR_HUD: VFR_HUD,
  RadioStatus: RadioStatus,
  WaypointReached: WaypointReached,
  LogData: LogData,
  GlobalPositionTarget: GlobalPositionTarget,
};
