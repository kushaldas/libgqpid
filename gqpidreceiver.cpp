#include <glib.h>
#include <qpid/messaging/Message.h>
#include <qpid/messaging/Receiver.h>
#include <qpid/messaging/Sender.h>
#include <qpid/messaging/Session.h>
#include <gqpidreceiver.h>
#include <gqpidmessage.h>

using namespace qpid::messaging;

struct _GQpidReceiver
{
    Receiver rcv;

    _GQpidReceiver (Session &s, const gchar *add)
    {
        rcv = s.createReceiver (add);
    }
};

GQpidReceiver*
g_qpid_receiver_new (Session &s, const gchar *add)
{
    GQpidReceiver *rcv;
    rcv = new GQpidReceiver (s, add);

    return rcv;
}

/**
 * g_qpid_receiver_fetch:
 * @rcv: a #GQpidReceiver* object
 * @duration: number of seconds as duration, pass -1 for
 *            FOREVER waiting.
 *
 * Fetches a message.
 *
 * Return value: a new created #GQpidMessage* instance.
 **/
GQpidMessage*
g_qpid_receiver_fetch (GQpidReceiver *rcv, int duration)
{
    g_return_val_if_fail (rcv !=NULL, NULL);
    Message m = rcv->rcv.fetch (Duration::SECOND * duration);
    return g_qpid_message_new_from_msg (m);
}



