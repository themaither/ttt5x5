/* optbus.c: Implementation of optbus using argp with static memory
   Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#include <config.h>

#include <stdio.h>

#ifndef TMLIB_OPTBUS
#define TMLIB_OPTBUS 1
#endif

#if TMLIB_OPTBUS
#include <stdlib.h>
#include <argp.h>
#include <assert.h>

enum {
  /* First 256 characters are reserved for ASCII characters, and it's
     better to not touch them */
  INDEX_BASE = 256,

  /* Limit of how many arguments you can push, you may change this value
     if you run out */
  OPTIONS_CAP = 256
};

const char *argp_program_version = PACKAGE_STRING;

const char *argp_program_bug_address = PACKAGE_BUGREPORT;

static struct argp_option options[OPTIONS_CAP] = {};

static void (*fn_table[OPTIONS_CAP])(void);

static int option_count = 0;

static struct argp argp;

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  switch (key)
    {
      case ARGP_KEY_ARG:
        if (state->arg_num >= 0)
          argp_usage (state);
        break;

      default:
        if (key >= 256)
          if (key < 256 + OPTIONS_CAP)
            if (fn_table[key - 256])
              {
                fn_table[key - 256] ();
                break;
              }
        return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

#endif /* TMLIB_OPTBUS */

void
optbus_init (void)
{
#if TMLIB_OPTBUS
  argp.options = options;
  argp.parser = parse_opt;
  argp.args_doc = 0;
  for (size_t i = 0; i < 256; ++i)
    {
      options[i].name  = NULL;
      options[i].key   = 0;
      options[i].arg   = 0;
      options[i].flags = 0;
      options[i].doc   = NULL;
      options[i].group = 0;

      fn_table[i] = NULL;
    }
#endif /* TMLIB_OPTBUS */
}

void
autodep_optbus_init (void)
{
#if TMLIB_OPTBUS
  static int imported = 0;

  if (imported)
    return;

  optbus_init ();
  imported = 1;
#endif /* TMLIB_OPTBUS */
}

void
optbus_doc (const char *doc)
{
#if TMLIB_OPTBUS
  argp.doc = doc;
#endif /* TMLIB_OPTBUS */
}

void
optbus_push (const char *name, const char *doc, void (*handler)(void))
{
#if TMLIB_OPTBUS
  options[option_count].name = name;
  options[option_count].key = 256 + option_count;
  options[option_count].arg = 0;
  options[option_count].flags = 0;
  options[option_count].doc = doc;
  options[option_count].group = 0;

  fn_table[option_count] = handler;
  ++option_count;
#endif /* TMLIB_OPTBUS */
}

void
optbus_parse (int argc, char **argv)
{
#if TMLIB_OPTBUS
  argp_parse (&argp, argc, argv, 0, 0, NULL);
#else
  if (argc != 1)
    fprintf (stderr, "%s: options are unsupported\n", argv[0]);
#endif /* TMLIB_OPTBUS */
}
