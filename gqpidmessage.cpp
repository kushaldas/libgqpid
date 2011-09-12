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

/**
 * g_qpid_message_new:
 * @text: the message text
 *
 * Creates a new message with the given text.
 *
 * Return value: a newly allocated #GQpidMessage.
 *   You must free it with g_qpid_message_free() when
 *   are finished with it.
 **/
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

/**
 * g_qpid_message_get_content:
 * @msg: a #GQpidMessage* object
 *
 * Gets the content of the message.
 *
 * Return value: it returns the message string as gchar*.
 **/
const gchar*
g_qpid_message_get_content (GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, NULL);

    std::string s = msg->msg.getContent ();

    return s.c_str ();
}

/**
 * g_qpid_message_set_subject:
 * @msg: a #GQpidMessage* object
 * @text: const gchar* of the actual subject
 *
 * Sets the given subject to the message.
 **/
void
g_qpid_message_set_subject (GQpidMessage *msg, const gchar *text)
{

    g_return_if_fail (msg != NULL);

    msg->msg.setSubject (text);
    return;
}

/**
 * g_qpid_message_get_subject:
 * @msg: a #GQpidMessage* object
 *
 * Gets the subject of the given message.
 *
 * Return value: a gchar* pointing to the subject of the mesaage.
 **/
const gchar*
g_qpid_message_get_subject (GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, NULL);

    std::string s = msg->msg.getSubject ();
    return s.c_str ();
}

/**
 * g_qpid_message_set_content_type:
 * @msg: a #GQpidMessage* object
 * @text: the content type string
 *
 * Sets the message content type
 **/
void
g_qpid_message_set_content_type (GQpidMessage *msg, const gchar *text)
{

    g_return_if_fail (msg != NULL);

    if (text != NULL)
        msg->msg.setContentType (text);
}

/**
 * g_qpid_message_get_content_type:
 * @msg: a #GQpidMessage* object
 *
 * Gets the message content type
 * Return value: a const gchar* holding the content type.
 **/
const gchar*
g_qpid_message_get_content_type (GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, NULL);

    std::string s = msg->msg.getContentType ();
    return s.c_str();
}

/**
 * g_qpid_message_set_userid:
 * @msg: a #GQpidMessage* object
 * @text: the userid as gchar*
 *
 * Sets the useid of the message
 **/
void
g_qpid_message_set_userid (GQpidMessage *msg, const gchar *text)
{

    g_return_if_fail (msg != NULL);

    if (text != NULL)
        msg->msg.setUserId (text);
}

/**
 * g_qpid_message_get_userid:
 * @msg: a #GQpidMessage* object
 *
 * Gets the message's userid.
 *
 * Return value: a const gchar* holding the userid of
 *               message.
 **/
const gchar*
g_qpid_message_get_userid (GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, NULL);

    std::string s = msg->msg.getUserId ();
    return s.c_str();
}

/**
 * g_qpid_message_set_priority:
 * @msg: a #GQpidMessage* object
 * @priority: int value
 *
 * Sets the priority of the message
 **/
void
g_qpid_message_set_priority (GQpidMessage *msg, const int priority)
{

    g_return_if_fail (msg != NULL);

    if (priority != 0)
        msg->msg.setPriority (priority);
}

/**
 * g_qpid_message_get_priority:
 * @msg: a #GQpidMessage* object
 *
 * Gets the message's priority.
 *
 * Return value: an integer
 **/
const int
g_qpid_message_get_priority (GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, -1);

    int i = msg->msg.getPriority ();
    return i;
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

void
g_qpid_message_release_session(GQpidMessage *msg, Session &s)
{

    g_return_if_fail (msg != NULL);

    s.release(msg->msg);
    return;
}
