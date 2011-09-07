#include <glib.h>
#include <qpid/messaging/Message.h>
#include <qpid/messaging/Receiver.h>
#include <qpid/messaging/Sender.h>
#include <qpid/messaging/Session.h>
#include <qpid/messaging/Connection.h>
#include <gqpidmessage.h>
#include <iostream>

using namespace qpid::messaging;

struct _GQpidMessage
{
    Message msg;

    _GQpidMessage(const gchar *add): msg(add)
    {

    }

    _GQpidMessage(Message &m): msg(m)
    {

    }
};


GQpidMessage*
g_qpid_message_new(gchar* text)
{
    GQpidMessage *msg;
    msg = new GQpidMessage (text);

    return msg;
}

GQpidMessage*
g_qpid_message_new_from_msg(Message &m)
{
    GQpidMessage *msg;
    msg = new GQpidMessage (m);

    return msg;
}

const gchar*
g_qpid_message_get_content(GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, NULL);

    std::string s = msg->msg.getContent();

    return s.c_str();
}

void
g_qpid_message_send(GQpidMessage *msg, Sender &s)
{

    g_return_if_fail (msg != NULL);

    s.send(msg->msg);
    return;
}

void
g_qpid_message_reject_session(GQpidMessage *msg, Session &s)
{

    g_return_if_fail (msg != NULL);

    s.reject(msg->msg);
    return;
}
