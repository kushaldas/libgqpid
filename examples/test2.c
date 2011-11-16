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

    sender = g_qpid_session_create_sender (ses,"amq.topic");
    receiver = g_qpid_session_create_receiver (ses, "amq.topic");

    msg1 = g_qpid_message_new ("Hello Kushal!");

    g_qpid_sender_send(sender, msg1);


    msg2 = g_qpid_receiver_fetch(receiver, -1);
    g_printf("%s\n", g_qpid_message_get_content(msg2));

    g_printf("%d\n", g_qpid_session_get_receivable(ses));

    /*g_qpid_session_acknowledge (ses);*/

    g_qpid_session_close (ses);
    g_qpid_session_free (ses);
    g_qpid_connection_close (conn);
    g_qpid_connection_free(conn);


    /*g_printf("%d\n", g_rec_area(rec));*/

    return 0;

}
