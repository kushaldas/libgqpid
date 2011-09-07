#include <glib.h>
#include <qpid/messaging/Message.h>
#include <qpid/messaging/Receiver.h>
#include <qpid/messaging/Sender.h>
#include <qpid/messaging/Session.h>
#include <gqpidsession.h>
#include <gqpidsender.h>
#include <gqpidreceiver.h>
#include <gqpidmessage.h>

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

gint
g_qpid_session_get_receivable (GQpidSession *s)
{
    g_return_val_if_fail (s != NULL, -1);

    return s->session.getReceivable();
}

void
g_qpid_session_acknowledge(GQpidSession *session)
{
    g_return_if_fail (session != NULL);

    session->session.acknowledge();
    return;
}

void
g_qpid_session_reject(GQpidSession *session, GQpidMessage *msg)
{
    g_return_if_fail (session != NULL);

    g_qpid_message_reject_session (msg, session->session);
    return;
}

void
g_qpid_session_close(GQpidSession *session)
{

    g_return_if_fail (session != NULL);

    session->session.close ();
}


void
g_qpid_session_free(GQpidSession *session)
{
    delete session;
}
