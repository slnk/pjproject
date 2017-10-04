/* $Id: log_writer_stdout.c 3553 2011-05-05 06:14:19Z nanang $ */
/* 
 * Copyright (C) 2008-2011 Teluu Inc. (http://www.teluu.com)
 * Copyright (C) 2003-2008 Benny Prijono <benny@prijono.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */
#include <pj/log.h>
#include <pj/os.h>
#include <pj/compat/stdfileio.h>

/* SPECTRALINK PATCH */
#include <jni.h>
#include <android/log.h>

static void term_set_color(int level)
{
#if defined(PJ_TERM_HAS_COLOR) && PJ_TERM_HAS_COLOR != 0
    pj_term_set_color(pj_log_get_color(level));
#else
    PJ_UNUSED_ARG(level);
#endif
}

static void term_restore_color(void)
{
#if defined(PJ_TERM_HAS_COLOR) && PJ_TERM_HAS_COLOR != 0
    /* Set terminal to its default color */
    pj_term_set_color(pj_log_get_color(77));
#endif
}


/* SPECTRALINK PATCH BELOW */

/////
// Android logging outputs a max of 1023 characters.  So break the message into smaller chunks to
// send to logcat.
//
// Android logging using a null terminated string so code below temporarily adds a null terminator.
/////
PJ_DEF(void) pj_split_and_write_log(char * start, int len)
{
    static const int BLOCK_SIZE = 1023;

    while (len > BLOCK_SIZE)
    {
        char * end = start + BLOCK_SIZE;
        char temp;
        while ((*end != '\n') && (*end != '\r'))
        {
            end--;
            if (end <= start)
            {
                // No CRLF in message for a clean split so just split at BLOCK_SIZE
                end = start + BLOCK_SIZE;
                break;
            }
        }
        temp = *end;
        *end = '\0';
        __android_log_print(ANDROID_LOG_VERBOSE, "SlnkSip", "%s", start);
        *end = temp;
        end++;
        len -= end - start;
        start = end;
    }
    if (len > 0)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "SlnkSip", "%s", start);
    }
}

/* end SPECTRALINK PATCH */



PJ_DEF(void) pj_log_write(int level, const char *buffer, int len)
{
    PJ_CHECK_STACK();

    /* SPECTRALINK PATCHES BELOW -- write to android logcat */

    /* Copy to terminal/file. */
    if (pj_log_get_decor() & PJ_LOG_HAS_COLOR) {
	term_set_color(level);
	printf("%s", buffer);
        pj_split_and_write_log(buffer, len);	term_restore_color();
    } else {
	printf("%s", buffer);
        pj_split_and_write_log(buffer, len);
    }
}

