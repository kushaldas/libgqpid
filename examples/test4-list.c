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
    GQpidMessage *msg1;
    GQpidMessage *msg2;
    GList *list = NULL;
    g_type_init();

    conn = g_qpid_connection_new ("localhost:5672");
    g_qpid_connection_open (conn);

    ses = g_qpid_connection_create_session (conn);

    sender = g_qpid_session_create_sender (ses,"amq.topic");

    GValue* v3 = NULL;
    v3 =  g_new0 (GValue, 1);
    g_value_init (v3, G_TYPE_STRING);
    g_value_set_static_string (v3,"Gnome");

    GValue* v4 = NULL;
    v4 =  g_new0 (GValue, 1);
    g_value_init (v4, G_TYPE_STRING);
    g_value_set_static_string (v4,"KDE");

    GValue* v5 = NULL;
    v5 =  g_new0 (GValue, 1);
    g_value_init (v5, G_TYPE_INT64);
    g_value_set_int64 (v5,42);


    list = g_list_append (list, v3);
    list = g_list_append (list, v4);
    list = g_list_append (list, v5);



    msg1 = g_qpid_message_new_empty ();
    g_qpid_message_set_list (msg1, list);

    g_qpid_message_set_content_type (msg1, "amqp/list");
    g_qpid_message_set_subject (msg1, "With love");
    g_qpid_message_set_userid (msg1, "firebreather");
    g_qpid_message_set_priority (msg1, 5);

    g_qpid_sender_send(sender, msg1);

    g_qpid_session_close (ses);
    g_qpid_session_free (ses);
    g_qpid_connection_close (conn);
    g_qpid_connection_free(conn);

    return 0;

}
