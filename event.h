#ifndef EVENT_H
#define EVENT_H

// Event base class
class Event {
public:
    Event() {}
    virtual ~Event() {}

    // Method to be implemented by subclasses
    virtual void process() = 0;
};

#endif