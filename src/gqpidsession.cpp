/*
 * Copyright (c) 2011 Kushal Das <kdas@redhat.com>
 *
 * Licesed under MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


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
        session = c.createSession ();
    }
};

GQpidSession*
g_qpid_session_new (Connection &c)
{
    GQpidSession *session;
    session = new GQpidSession (c);

    return session;
}

/**
 * g_qpid_session_create_sender:
 * @session: a #GQpidSession* object
 * @add: gchar* used as address of sender
 *
 * Creates a new sender object.
 *
 * Return value: a newly allocated #GQpidSender.
 *   You must close it with g_qpid_sender_close()
 *   and then free it with g_qpid_sender_free() when
 *   are finished with it.
 **/
GQpidSender*
g_qpid_session_create_sender(GQpidSession *session, gchar *add)
{
    g_return_val_if_fail (session != NULL, NULL);
    GQpidSender *sender = g_qpid_sender_new (session->session, add);

    return sender;
}

/**
 * g_qpid_session_create_receiver:
 * @session: a #GQpidSession* object
 * @add: gchar* used as address of receiver
 *
 * Creates a new receiver object.
 *
 * Return value: a newly allocated #GQpidReceiver.
 *   You must close it with g_qpid_receiver_close()
 *   and then free it with g_qpid_receiver_free() when
 *   are finished with it.
 **/
GQpidReceiver*
g_qpid_session_create_receiver(GQpidSession *session, gchar *add)
{
    g_return_val_if_fail (session != NULL, NULL);
    GQpidReceiver *rcv = g_qpid_receiver_new (session->session, add);

    return rcv;
}

/**
 * g_qpid_session_create_receiver:
 * @session: a #GQpidSession* object
 *
 * Returns the total number of messages received and waiting to be
 * fetched by all Receivers belonging to this session.
 *
 * Return value: This is the total number of available messages
 * across all receivers on this session.
 **/
gint
g_qpid_session_get_receivable (GQpidSession *s)
{
    g_return_val_if_fail (s != NULL, -1);

    return s->session.getReceivable ();
}

/**
 * g_qpid_session_acknowledge:
 * @session: a #GQpidSession* object
 *
 * Acknowledges all outstanding messages that have
 * been received by the application on this session.
 **/
void
g_qpid_session_acknowledge (GQpidSession *session)
{
    g_return_if_fail (session != NULL);

    session->session.acknowledge ();
    return;
}

/**
 * g_qpid_session_release:
 * @session: a #GQpidSession* object
 * @msg: a #GQpidMessage* message
 *
 * Releases the specified message.
 **/
void
g_qpid_session_release (GQpidSession *session, GQpidMessage *msg)
{
    g_return_if_fail (session != NULL);

    g_qpid_message_release_session (msg, session->session);
    return;
}

/**
 * g_qpid_session_reject:
 * @session: a #GQpidSession* object
 * @msg: a #GQpidMessage* message
 *
 * Rejects the specified message.
 **/
void
g_qpid_session_reject (GQpidSession *session, GQpidMessage *msg)
{
    g_return_if_fail (session != NULL);

    g_qpid_message_reject_session (msg, session->session);
    return;
}

/**
 * g_qpid_session_close:
 * @session: a #GQpidSession* object
 *
 * Closes the session.
 **/
void
g_qpid_session_close (GQpidSession *session)
{

    g_return_if_fail (session != NULL);

    session->session.close ();
}

/**
 * g_qpid_session_free:
 * @session: a #GQpidSession* object
 *
 * Frees the session, must be called after you close the
 * session.
 **/
void
g_qpid_session_free (GQpidSession *session)
{
    delete session;
}
