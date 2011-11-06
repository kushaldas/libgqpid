#include <glib.h>

#ifdef __cplusplus
#include <qpid/messaging/Sender.h>
#include <qpid/messaging/Receiver.h>
#include <qpid/messaging/Session.h>
#include <qpid/messaging/Connection.h>
#include <qpid/messaging/Message.h>
#endif

typedef struct _GQpidMessage GQpidMessage;
#ifdef __cplusplus
void                            g_qpid_message_send             (GQpidMessage *, qpid::messaging::Sender&);
GQpidMessage*                   g_qpid_message_new_from_msg     (qpid::messaging::Message&);
void                            g_qpid_message_release_session  (GQpidMessage *, qpid::messaging::Session&);
void                            g_qpid_message_reject_session   (GQpidMessage *, qpid::messaging::Session&);
extern "C" {
#endif
GQpidMessage*                   g_qpid_message_new_empty        (void);
GQpidMessage*                   g_qpid_message_new              (gchar*);
const gchar*                    g_qpid_message_get_content      (GQpidMessage *);
void                            g_qpid_message_set_subject      (GQpidMessage *, const gchar *);
const gchar*                    g_qpid_message_get_subject      (GQpidMessage *);
void                            g_qpid_message_set_content_type (GQpidMessage *, const gchar *);
const gchar*                    g_qpid_message_get_content_type (GQpidMessage *);
void                            g_qpid_message_set_userid       (GQpidMessage *, const gchar *);
const gchar*                    g_qpid_message_get_userid       (GQpidMessage *);
void                            g_qpid_message_set_priority     (GQpidMessage *, const int);
const int                       g_qpid_message_get_priority     (GQpidMessage *);
GHashTable*                     g_qpid_message_get_hashtable    (GQpidMessage *);
void                            g_qpid_message_set_hashtable    (GQpidMessage *, GHashTable *);
GList*                          g_qpid_message_get_list         (GQpidMessage *);
void                            g_qpid_message_set_list         (GQpidMessage *, GList *);
void                            g_qpid_message_set_durable      (GQpidMessage *, gboolean);
gboolean                        g_qpid_message_get_durable      (GQpidMessage *);
#ifdef __cplusplus
}
#endif
