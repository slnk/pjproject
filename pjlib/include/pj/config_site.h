
#define PJ_CONFIG_ANDROID   1
/*
 * Android sample settings.
 */
#if PJ_CONFIG_ANDROID

/*
 * PJLIB settings.
 */

/* Disable floating point support */
#undef PJ_HAS_FLOATING_POINT
#define PJ_HAS_FLOATING_POINT		0

/*
 * PJMEDIA settings
 */

/* We have our own OpenSL ES backend */
#define PJMEDIA_AUDIO_DEV_HAS_PORTAUDIO	0
#define PJMEDIA_AUDIO_DEV_HAS_WMME		0
#define PJMEDIA_AUDIO_DEV_HAS_OPENSL        0
#define PJMEDIA_AUDIO_DEV_HAS_ANDROID_JNI	1

/* Disable some codecs */
#define PJMEDIA_HAS_L16_CODEC		0
//#define PJMEDIA_HAS_G722_CODEC		0

/* Fine tune Speex's default settings for best performance/quality */
#define PJMEDIA_CODEC_SPEEX_DEFAULT_QUALITY	5

/*
 * PJSIP settings.
 */

/* Increase allowable packet size, just in case */
//#define PJSIP_MAX_PKT_LEN			2000

/*
 * PJSUA settings.
 */

/* Default codec quality, previously was set to 5, however it is now
 * set to 4 to make sure pjsua instantiates resampler with small filter.
 */
#define PJSUA_DEFAULT_CODEC_QUALITY		4

/* Set maximum number of dialog/transaction/calls to minimum */
#define PJSIP_MAX_TSX_COUNT 		31
#define PJSIP_MAX_DIALOG_COUNT 		31
#define PJSUA_MAX_CALLS			4

/* Other pjsua settings */
#define PJSUA_MAX_ACC			4
#define PJSUA_MAX_PLAYERS			4
#define PJSUA_MAX_RECORDERS			4
#define PJSUA_MAX_CONF_PORTS		(PJSUA_MAX_CALLS+2*PJSUA_MAX_PLAYERS)
#define PJSUA_MAX_BUDDIES			32
#endif


/*
 * BB10
 */
#if defined(PJ_CONFIG_BB10) && PJ_CONFIG_BB10
/* Quality 3 - 4 to use resampling small filter */
    #define PJSUA_DEFAULT_CODEC_QUALITY			4
    #define PJMEDIA_HAS_LEGACY_SOUND_API		0
    #undef PJMEDIA_HAS_SPEEX_AEC
    #define PJMEDIA_HAS_SPEEX_AEC			0
    #undef PJMEDIA_AUDIO_DEV_HAS_PORTAUDIO
    #define PJMEDIA_AUDIO_DEV_HAS_PORTAUDIO		0
    #undef PJMEDIA_AUDIO_DEV_HAS_ALSA
    #define PJMEDIA_AUDIO_DEV_HAS_ALSA			0
#endif


/*
 * Minimum size
 */
#ifdef PJ_CONFIG_MINIMAL_SIZE

#   undef PJ_OS_HAS_CHECK_STACK
#   define PJ_OS_HAS_CHECK_STACK	0
#   define PJ_LOG_MAX_LEVEL		0
#   define PJ_ENABLE_EXTRA_CHECK	0
#   define PJ_HAS_ERROR_STRING		0
#   undef PJ_IOQUEUE_MAX_HANDLES
/* Putting max handles to lower than 32 will make pj_fd_set_t size smaller
 * than native fdset_t and will trigger assertion on sock_select.c.
 */
#   define PJ_IOQUEUE_MAX_HANDLES	32
#   define PJ_CRC32_HAS_TABLES		0
#   define PJSIP_MAX_TSX_COUNT		15
#   define PJSIP_MAX_DIALOG_COUNT	15
#   define PJSIP_UDP_SO_SNDBUF_SIZE	4000
#   define PJSIP_UDP_SO_RCVBUF_SIZE	4000
#   define PJMEDIA_HAS_ALAW_ULAW_TABLE	0

#elif defined(PJ_CONFIG_MAXIMUM_SPEED)
#   define PJ_SCANNER_USE_BITWISE	0
#   undef PJ_OS_HAS_CHECK_STACK
#   define PJ_OS_HAS_CHECK_STACK	0
#   define PJ_LOG_MAX_LEVEL		3
#   define PJ_ENABLE_EXTRA_CHECK	0
#   define PJ_IOQUEUE_MAX_HANDLES	5000
#   define PJSIP_MAX_TSX_COUNT		((640*1024)-1)
#   define PJSIP_MAX_DIALOG_COUNT	((640*1024)-1)
#   define PJSIP_UDP_SO_SNDBUF_SIZE	(24*1024*1024)
#   define PJSIP_UDP_SO_RCVBUF_SIZE	(24*1024*1024)
#   define PJ_DEBUG			0
#   define PJSIP_SAFE_MODULE		0
#   define PJ_HAS_STRICMP_ALNUM		0
#   define PJSIP_UNESCAPE_IN_PLACE	1

#   if defined(PJ_WIN32) || defined(PJ_WIN64)
#     define PJSIP_MAX_NET_EVENTS	10
#   endif

#   define PJSUA_MAX_CALLS		512

#endif

