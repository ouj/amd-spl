#ifndef AMDSPL_BUFFER_INTERFACE_H
#define AMDSPL_BUFFER_INTERFACE_H
namespace amdspl
{
    namespace core
    {
        namespace cal
        {
            class Event;
            class IBuffer
            {
            public:
                virtual CALresource     getResHandle() = 0;
                virtual CALformat       getFormat() = 0;
                virtual unsigned int    getWidth() = 0;
                virtual unsigned int    getHeight() = 0;

                virtual bool            setInputEvent(Event* e) = 0;
                virtual bool            setOutputEvent(Event* e) = 0;
                virtual void            waitInputEvent() = 0;
                virtual void            waitOutputEvent() = 0;

                virtual bool            isGlobal() = 0;
            };
        }
    }
}
#endif //AMDSPL_BUFFER_INTERFACE_H