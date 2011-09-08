#include <glib.h>
#include <qpid/messaging/Message.h>
#include <qpid/messaging/Receiver.h>
#include <qpid/messaging/Sender.h>
#include <qpid/messaging/Session.h>
#include <gqpidsender.h>
#include <gqpidmessage.h>

using namespace qpid::messaging;

struct _GQpidSender
{
    Sender sender;

    _GQpidSender(Session &s, const gchar *add)
    {
        sender = s.createSender (add);
    }
};

GQpidSender*
g_qpid_sender_new (Session &s, const gchar *add)
{
    GQpidSender *sender;
    sender = new GQpidSender (s, add);

    return sender;
}

/**
 * g_qpid_sender_send:
 * @sender: a #GQpidSender* object
 * @msg: a #GQpidMessage object which to be send
 *
 * It sends the message.
 **/
void
g_qpid_sender_send (GQpidSender *sender,
                    GQpidMessage  *msg)
{
    g_return_if_fail (msg != NULL);

    g_qpid_message_send (msg, sender->sender);
}


