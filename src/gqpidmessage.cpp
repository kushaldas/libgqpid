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
#include <glib-object.h>
#include <qpid/messaging/Message.h>
#include <qpid/messaging/Receiver.h>
#include <qpid/messaging/Sender.h>
#include <qpid/messaging/Session.h>
#include <qpid/messaging/Connection.h>
#include <gqpidmessage.h>
#include <string.h>
#include <iostream>

using namespace qpid::messaging;
using namespace qpid::types;

GHashTable* _internal_createhash (Variant::Map &);
void _send_createcontent (Variant::Map &content, GHashTable *hash);

struct _GQpidMessage
{
    Message msg;

    _GQpidMessage(const gchar *add): msg(add)
    {

    }

    _GQpidMessage(Message &m): msg(m)
    {

    }

    _GQpidMessage(): msg()
    {

    }

};

/**
 * g_qpid_message_new_empty:
 *
 * Creates a new message.
 *
 * Return value: a newly allocated #GQpidMessage.
 *   You must free it with g_qpid_message_free() when
 *   are finished with it.
 **/
GQpidMessage*
g_qpid_message_new_empty ()
{
    GQpidMessage *msg;
    msg = new GQpidMessage ();

    return msg;
}

/**
 * g_qpid_message_new:
 * @text: the message text
 *
 * Creates a new message with the given text.
 *
 * Return value: a newly allocated #GQpidMessage.
 *   You must free it with g_qpid_message_free() when
 *   are finished with it.
 **/
GQpidMessage*
g_qpid_message_new(gchar* text)
{
    GQpidMessage *msg;
    msg = new GQpidMessage (text);

    return msg;
}

GQpidMessage*
g_qpid_message_new_from_msg(Message &m)
{
    GQpidMessage *msg;
    msg = new GQpidMessage (m);

    return msg;
}

/**
 * g_qpid_message_get_content:
 * @msg: a #GQpidMessage* object
 *
 * Gets the content of the message.
 *
 * Return value: it returns the message string as gchar*.
 **/
const gchar*
g_qpid_message_get_content (GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, NULL);

    std::string s = msg->msg.getContent ();

    return s.c_str ();
}

/**
 * g_qpid_message_set_subject:
 * @msg: a #GQpidMessage* object
 * @text: const gchar* of the actual subject
 *
 * Sets the given subject to the message.
 **/
void
g_qpid_message_set_subject (GQpidMessage *msg, const gchar *text)
{

    g_return_if_fail (msg != NULL);

    msg->msg.setSubject (text);
    return;
}

/**
 * g_qpid_message_get_subject:
 * @msg: a #GQpidMessage* object
 *
 * Gets the subject of the given message.
 *
 * Return value: a gchar* pointing to the subject of the mesaage.
 **/
const gchar*
g_qpid_message_get_subject (GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, NULL);

    std::string s = msg->msg.getSubject ();
    return s.c_str ();
}

/**
 * g_qpid_message_set_content_type:
 * @msg: a #GQpidMessage* object
 * @text: the content type string
 *
 * Sets the message content type
 **/
void
g_qpid_message_set_content_type (GQpidMessage *msg, const gchar *text)
{

    g_return_if_fail (msg != NULL);

    if (text != NULL)
        msg->msg.setContentType (text);
}

/**
 * g_qpid_message_get_content_type:
 * @msg: a #GQpidMessage* object
 *
 * Gets the message content type
 * Return value: a const gchar* holding the content type.
 **/
const gchar*
g_qpid_message_get_content_type (GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, NULL);

    std::string s = msg->msg.getContentType ();
    return s.c_str();
}

/**
 * g_qpid_message_set_userid:
 * @msg: a #GQpidMessage* object
 * @text: the userid as gchar*
 *
 * Sets the useid of the message
 **/
void
g_qpid_message_set_userid (GQpidMessage *msg, const gchar *text)
{

    g_return_if_fail (msg != NULL);

    if (text != NULL)
        msg->msg.setUserId (text);
}

/**
 * g_qpid_message_get_userid:
 * @msg: a #GQpidMessage* object
 *
 * Gets the message's userid.
 *
 * Return value: a const gchar* holding the userid of
 *               message.
 **/
const gchar*
g_qpid_message_get_userid (GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, NULL);

    std::string s = msg->msg.getUserId ();
    return s.c_str();
}

/**
 * g_qpid_message_set_priority:
 * @msg: a #GQpidMessage* object
 * @priority: int value
 *
 * Sets the priority of the message
 **/
void
g_qpid_message_set_priority (GQpidMessage *msg, const int priority)
{

    g_return_if_fail (msg != NULL);

    if (priority != 0)
        msg->msg.setPriority (priority);
}

/**
 * g_qpid_message_get_priority:
 * @msg: a #GQpidMessage* object
 *
 * Gets the message's priority.
 *
 * Return value: an integer
 **/
const int
g_qpid_message_get_priority (GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, -1);

    int i = msg->msg.getPriority ();
    return i;
}


GList*
_internal_createlist (Variant::List &content)
{
    GList *list = NULL;
    for (Variant::List::const_iterator ci = content.begin(); ci != content.end(); ++ci)
    {
        Variant value = *ci;
        GValue* v = NULL;
        v =  g_new0 (GValue, 1);

        /* Prints the Variant type
         * for debug purpose only
        std::cout << getTypeName(value.getType()) << std::endl;*/

        if (getTypeName(value.getType()) == "string")
        {
            g_value_init (v, G_TYPE_STRING);
            std::string s = value.getString();
            g_value_set_string (v,(gchar*) s.c_str());
        }else if (getTypeName(value.getType()) == "double")
        {
            g_value_init (v, G_TYPE_DOUBLE);
            double f = value.asDouble ();
            g_value_set_double (v, f);
        }else if (getTypeName(value.getType()) == "int64")
        {
            g_value_init (v, G_TYPE_INT64);
            gint64 f = value.asInt64 ();
            g_value_set_int64 (v, f);
        }else if (getTypeName(value.getType()) == "bool")
        {
            g_value_init (v, G_TYPE_BOOLEAN);
            gboolean b = value.asBool ();
            g_value_set_boolean (v, b);
        }else if (getTypeName(value.getType()) == "map")
        {

            GHashTable* h;
            g_value_init (v, G_TYPE_HASH_TABLE);
            Variant::Map m = value.asMap ();

            h = _internal_createhash (m);

            g_value_set_boxed (v, h);
        }else if (getTypeName(value.getType()) == "list")
        {

            GList* h;
            g_value_init (v, G_TYPE_POINTER);
            Variant::List l = value.asList ();

            h = _internal_createlist (l);

            g_value_set_pointer (v, h);
        }
        list = g_list_append (list, v);

    }
    return list;
}


GHashTable*
_internal_createhash (Variant::Map &content)
{
    GHashTable* hash;
    hash =  g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);
    for(std::map<std::string, Variant>::iterator it = content.begin(); it != content.end(); ++it)
    {
        std::string key  = it->first;
        Variant value = it->second;
        GValue* v = NULL;
        v =  g_new0 (GValue, 1);

        gchar *k = (gchar*) key.c_str();
        /* Prints the Variant type
         * for debug purpose only
        std::cout << getTypeName(value.getType()) << std::endl;*/

        if (getTypeName(value.getType()) == "string")
        {
            g_value_init (v, G_TYPE_STRING);
            std::string s = value.getString();
            g_value_set_string (v,(gchar*) s.c_str());
            g_hash_table_insert (hash, k, v);
        }else if (getTypeName(value.getType()) == "double")
        {
            g_value_init (v, G_TYPE_DOUBLE);
            double f = value.asDouble ();
            g_value_set_double (v, f);
            g_hash_table_insert (hash, k, v);
        }else if (getTypeName(value.getType()) == "int64")
        {
            g_value_init (v, G_TYPE_INT64);
            gint64 f = value.asInt64 ();
            g_value_set_int64 (v, f);
            g_hash_table_insert (hash, k, v);
        }else if (getTypeName(value.getType()) == "bool")
        {
            g_value_init (v, G_TYPE_BOOLEAN);
            gboolean b = value.asBool ();
            g_value_set_boolean (v, b);
            g_hash_table_insert (hash, k, v);
        }else if (getTypeName(value.getType()) == "map")
        {

            GHashTable* h;
            g_value_init (v, G_TYPE_HASH_TABLE);
            Variant::Map m = value.asMap ();

            h = _internal_createhash (m);

            g_value_set_boxed (v, h);
            g_hash_table_insert (hash, k, v);
        }else if (getTypeName(value.getType()) == "list")
        {

            GList* h;
            g_value_init (v, G_TYPE_POINTER);
            Variant::List l = value.asList ();

            h = _internal_createlist (l);

            g_value_set_pointer (v, h);
            g_hash_table_insert (hash, k, v);
        }


    }

    return hash;
}

/**
 * g_qpid_message_get_hashtable:
 * @msg: a #GQpidMessage* object
 *
 * Gets the message's content as a GHashTable*.
 *
 * Return value: GHashTable*
 **/
GHashTable*
g_qpid_message_get_hashtable (GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, NULL);
    Variant::Map content;

    GHashTable* hash = NULL;

    decode(msg->msg, content);

    hash = _internal_createhash (content);

    return hash;
}

/**
 * g_qpid_message_get_list:
 * @msg: a #GQpidMessage* object
 *
 * Gets the message's content as a GList*.
 *
 * Return value: GList*
 **/
GList*
g_qpid_message_get_list (GQpidMessage *msg)
{

    g_return_val_if_fail (msg != NULL, NULL);
    Variant::List content;

    GList* list = NULL;

    decode(msg->msg, content);

    list = _internal_createlist (content);

    return list;
}

void
_send_createlist (Variant::List &content, GList *list)
{
    while(1)
    {
        GValue *value = (GValue*) list->data;

        //std::cout << G_VALUE_TYPE_NAME (value) << std::endl;
        /* do something with key and value */
        if (strcmp ("gchararray", G_VALUE_TYPE_NAME (value)) == 0 ) {
            content.push_back (g_value_get_string ((GValue*)value));
        }
        if (strcmp("gdouble", G_VALUE_TYPE_NAME (value)) == 0)
            content.push_back (g_value_get_double ((GValue*)value));
        if (strcmp("gint64", G_VALUE_TYPE_NAME (value)) == 0)
            content.push_back (g_value_get_int64 ((GValue*)value));
        if (strcmp("gboolean", G_VALUE_TYPE_NAME (value)) == 0)
            content.push_back (g_value_get_boolean ((GValue*)value));
        if (strcmp("GHashTable", G_VALUE_TYPE_NAME (value)) == 0)
        {
            Variant::Map c;
            _send_createcontent (c, (GHashTable*) g_value_get_boxed((GValue*)value));
            content.push_back (c);
        }
        if ( strcmp("gpointer", G_VALUE_TYPE_NAME (value)) == 0)
        {
            GList* l = (GList*) g_value_get_pointer (value);
            Variant::List list2;
            _send_createlist (list2, l);
            content.push_back (list2);
        }
        /* Check if there are more entries */
        if (list->next == NULL)
            break;
        list = list->next;

    }
}

void
_send_createcontent (Variant::Map &content, GHashTable *hash)
{
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hash);

    while (g_hash_table_iter_next (&iter, &key, &value))
    {
        std::cout << G_VALUE_TYPE_NAME (value) << std::endl;
        /* do something with key and value */
        if (strcmp ("gchararray", G_VALUE_TYPE_NAME (value)) == 0 ) {
            content[(gchar*) key] = g_value_get_string ((GValue*)value);
        }
        if (strcmp("gdouble", G_VALUE_TYPE_NAME (value)) == 0)
            content[(gchar*) key] = g_value_get_double ((GValue*)value);
        if (strcmp("gint64", G_VALUE_TYPE_NAME (value)) == 0)
            content[(gchar*) key] = g_value_get_int64 ((GValue*)value);
        if (strcmp("gboolean", G_VALUE_TYPE_NAME (value)) == 0)
            content[(gchar*) key] = g_value_get_boolean ((GValue*)value);
        if (strcmp("GHashTable", G_VALUE_TYPE_NAME (value)) == 0)
        {
            Variant::Map c;
            _send_createcontent (c, (GHashTable*) g_value_get_boxed((GValue*)value));
            content[(gchar*) key] = c;
        }
        if ( strcmp("gpointer", G_VALUE_TYPE_NAME (value)) == 0)
        {
            GList* l = (GList*) g_value_get_pointer ((GValue*)value);
            Variant::List list;
            _send_createlist (list, l);
            content[(gchar*) key] = list;
        }
    }
}

/**
 * g_qpid_message_set_hashtable:
 * @msg: a #GQpidMessage* object
 * @hash: a #GHashTable* object
 *
 * Sets the message's content as a GHashTable*.
 **/
void
g_qpid_message_set_hashtable (GQpidMessage *msg, GHashTable *hash)
{

    g_return_if_fail (msg != NULL);
    Variant::Map content;

    _send_createcontent (content, hash);

    encode (content, msg->msg);

    return;
}

/**
 * g_qpid_message_set_list:
 * @msg: a #GQpidMessage* object
 * @hash: a #GList* object
 *
 * Sets the message's content as a GList*.
 **/
void
g_qpid_message_set_list (GQpidMessage *msg, GList *list)
{

    g_return_if_fail (msg != NULL);
    Variant::List content;

    _send_createlist (content, list);

    encode (content, msg->msg);

    return;
}

void
g_qpid_message_send(GQpidMessage *msg, Sender &s)
{

    g_return_if_fail (msg != NULL);

    s.send (msg->msg, true);
    return;
}

void
g_qpid_message_reject_session(GQpidMessage *msg, Session &s)
{

    g_return_if_fail (msg != NULL);

    s.reject(msg->msg);
    return;
}

void
g_qpid_message_release_session(GQpidMessage *msg, Session &s)
{

    g_return_if_fail (msg != NULL);

    s.release(msg->msg);
    return;
}

void
g_qpid_message_set_durable(GQpidMessage *msg, gboolean val)
{
    g_return_if_fail (msg != NULL);

    msg->msg.setDurable(val);
    return;
}

gboolean
g_qpid_message_get_durable(GQpidMessage *msg)
{
    g_return_val_if_fail (msg != NULL, FALSE);

    gboolean data = msg->msg.getDurable ();
    return data;
}
