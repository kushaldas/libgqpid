#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gqpid.h>

int main() {
    GQpidConnection *conn;
    GQpidSession *ses;
    GQpidSender *sender;
    GQpidReceiver *receiver;
    GQpidMessage *msg1;
    GQpidMessage *msg2;
    g_type_init();

    conn = g_qpid_connection_new ("localhost:5672");
    g_qpid_connection_open (conn);
    g_printf("%d\n",g_qpid_connection_is_open (conn));

    ses = g_qpid_connection_create_session (conn);

    receiver = g_qpid_session_create_receiver (ses, "amq.topic");


    msg2 = g_qpid_receiver_fetch(receiver, -1);
    g_printf("%s\n", g_qpid_message_get_content(msg2));


    /*g_qpid_session_acknowledge (ses);*/

    g_qpid_session_close (ses);
    g_qpid_session_free (ses);
    g_qpid_connection_close (conn);
    g_qpid_connection_free(conn);

    return 0;

}
