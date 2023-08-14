#include "zigbee_device_mocker.h"
#include "event.h"
#include "join_event.h"
#include "leave_event.h"

void ZigbeeDeviceMocker::reportEvent(Event *event) {
    process_event(event);
}

void ZigbeeDeviceMocker::deviceAnnouncement() {
    Event *event = new DeviceAnnouncementEvent();
    reportEvent(event);
}

void ZigbeeDeviceMocker::deviceLeave() {
    Event *event = new LeaveEvent();
    reportEvent(event);
}

void ZigbeeDeviceMocker::deviceJoin() {
    Event *event = new JoinEvent();
    reportEvent(event);
}

void ZigbeeDeviceMocker::deviceReporting() {
    Event *event = new ReportingEvent();
    reportEvent(event);
}