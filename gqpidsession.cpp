#include <glib.h>
#include <qpid/messaging/Message.h>
#include <qpid/messaging/Receiver.h>
#include <qpid/messaging/Sender.h>
#include <qpid/messaging/Session.h>
#include <gqpidsession.h>
#include <gqpidsender.h>
#include <gqpidreceiver.h>

using namespace qpid::messaging;

struct _GQpidSession
{
    Session session;

    _GQpidSession(Connection &c)
    {
        session = c.createSession();
    }
};

GQpidSession*
g_qpid_session_new(Connection &c)
{
    GQpidSession *session;
    session = new GQpidSession (c);

    return session;
}

GQpidSender*
g_qpid_session_create_sender(GQpidSession *session, gchar *add)
{
    g_return_val_if_fail (session != NULL, NULL);
    GQpidSender *sender = g_qpid_sender_new (session->session, add);

    return sender;
}

GQpidReceiver*
g_qpid_session_create_receiver(GQpidSession *session, gchar *add)
{
    g_return_val_if_fail (session != NULL, NULL);
    GQpidReceiver *rcv = g_qpid_receiver_new (session->session, add);

    return rcv;
}
void
g_qpid_session_acknowledge(GQpidSession *session)
{
    g_return_if_fail (session != NULL);

    session->session.acknowledge();
    return;
}

