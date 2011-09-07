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


GQpidConnection*
g_qpid_connection_new(gchar* broker)
{
    GQpidConnection *conn;
    conn = new GQpidConnection (broker);

    return conn;
}

void
g_qpid_connection_open(GQpidConnection *conn)
{

    g_return_if_fail (conn != NULL);

    conn->conn.open ();

}

GQpidSession*
g_qpid_connection_create_session(GQpidConnection *conn)
{
    g_return_val_if_fail (conn != NULL, NULL);


    GQpidSession *session = g_qpid_session_new (conn->conn);

    return session;
}

void
g_qpid_connection_close(GQpidConnection *conn)
{

    g_return_if_fail (conn != NULL);

    conn->conn.close ();
}

