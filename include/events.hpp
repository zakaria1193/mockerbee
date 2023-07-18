#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <vector>

namespace event {

// Base event class
class Event {
public:
    virtual ~Event() = default;
};

// Device announcement event
class DeviceAnnouncementEvent : public Event {
  Device& device;

public:
  explicit DeviceAnnouncementEvent(Device& device) : device(device) {}

  [[nodiscard]] Device& get_device() const { return device; }
};

// Reporting event
class ReportingEvent : public Event {
};

// Event handler interface
class IEventHandler {
public:
    virtual void handleEvent(const Event& event) = 0;
    virtual ~IEventHandler() = default;
};

// Zigbee device mocker
class ZigbeeDeviceMocker {
private:
    std::vector<IEventHandler*> eventHandlers;  // Event handler interface pointers

public:
    // Register an event handler
    void registerEventHandler(IEventHandler* handler) {
        eventHandlers.push_back(handler);
    }

    // Emit an event and notify all registered event handlers
    void emitEvent(const Event& event) {
        for (auto handler : eventHandlers) {
            handler->handleEvent(event);
        }
    }
};

}  // namespace event

#endif // EVENTS_HPP
