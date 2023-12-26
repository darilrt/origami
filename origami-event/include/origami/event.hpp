#pragma once

#include <origami/core.hpp>
#include <origami/type_id.hpp>

#include <unordered_map>
#include <vector>
#include <functional>

#define Event(T) \
    struct T;

using EventHandler = std::function<void(EngineState &, void *)>;

class EventSystem : public Resource
{
public:
    void init(EngineState &state);

    template <typename T>
    void regist(EventHandler handler)
    {
        event_handlers[TypeID<T>::value()].push_back(handler);
    }

    template <typename T>
    void emit(T event)
    {
        for (auto &handler : event_handlers[TypeID<T>::value()])
        {
            handler(*state, (void *)&event);
        }
    }

    template <typename T>
    void emit()
    {
        for (auto &handler : event_handlers[TypeID<T>::value()])
        {
            handler(*state, nullptr);
        }
    }

private:
    EngineState *state;
    std::unordered_map<typeid_t, std::vector<EventHandler>> event_handlers;
};

Event(Start);
Event(PreUpdate);
Event(Update { float delta_time; });
Event(PostUpdate);
Event(Render);
Event(Stop);