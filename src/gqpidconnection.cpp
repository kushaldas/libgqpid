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
#include <qpid/messaging/Connection.h>
#include <gqpidconnection.h>
#include <gqpidsession.h>
#include <iostream>

using namespace qpid::messaging;

struct _GQpidConnection
{
    Connection conn;

    _GQpidConnection(const gchar *broker): conn(broker, "") {}
};

/**
 * g_qpid_connection_new:
 * @broker: the broker name
 *
 * Creates a new connection to the given qpid broker.
 *
 * Return value: a newly allocated #GQpidConnection.
 *   You must close it with g_qpid_connection_close()
 *   and then free it with g_qpid_connection_free() when
 *   are finished with it.
 **/

GQpidConnection*
g_qpid_connection_new (gchar* broker)
{
    GQpidConnection *conn;
    conn = new GQpidConnection (broker);

    return conn;
}

/**
 * g_qpid_connection_open:
 * @conn: an instance of #GQpidConnection*
 *
 * Opens the given connection.
 **/
void
g_qpid_connection_open (GQpidConnection *conn)
{

    g_return_if_fail (conn != NULL);

    conn->conn.open ();

}

/**
 * g_qpid_connection_create_session:
 * @conn: an instance of #GQpidConnection*
 *
 * Creates a new #GQPidSession object from the connection
 * and returns it.
 *
 * Return value: a newly allocated #GQpidSession object. You
 *   must free it with g_qpid_session_free after you are
 *   finished wit it.
 **/
GQpidSession*
g_qpid_connection_create_session (GQpidConnection *conn)
{
    g_return_val_if_fail (conn != NULL, NULL);


    GQpidSession *session = g_qpid_session_new (conn->conn);

    return session;
}

/**
 * g_qpid_connection_is_open:
 * @conn: an instance of #GQpidConnection*
 *
 * Cheacks if the given is open or not.
 *
 * Return value: TRUE if the connection is open or
 *   returns FALSE.
 **/
gboolean
g_qpid_connection_is_open (GQpidConnection *conn)
{

    g_return_val_if_fail (conn != NULL, FALSE);

    gboolean b = conn->conn.isOpen ();
    return b;

}

/**
 * g_qpid_connection_close:
 * @conn: an instance of #GQpidConnection*
 *
 * Closes the connection.
 **/
void
g_qpid_connection_close (GQpidConnection *conn)
{

    g_return_if_fail (conn != NULL);

    conn->conn.close ();
}


/**
 * g_qpid_connection_free:
 * @conn: an instance of #GQpidConnection*
 *
 * Deallocates all memory and frees the object. Must be
 * called after you close the connection object.
 **/
void
g_qpid_connection_free (GQpidConnection *conn)
{
    delete conn;
}
