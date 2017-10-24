#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "cli.h"
#include "cli-cmd.h"
#include "cli-mem-types.h"
#include "cli1-xdr.h"
#include "run.h"
#include "syscall.h"
#include "common-utils.h"
#include "events.h"



int
cli_cmd_ourscli_help_cbk (struct cli_state *state, struct cli_cmd_word *in_word,
                      const char **words, int wordcount);
struct cli_cmd ourscli_cmds[] = {
        { "ourscli  help",
          cli_cmd_ourscli_help_cbk,
          "Hello world,this is our first gluster cli command"},

        { NULL, NULL, NULL }
};

int
cli_cmd_ourscli_help_cbk (struct cli_state *state, struct cli_cmd_word *in_word,
                      const char **words, int wordcount)
{
        struct cli_cmd        *cmd     = NULL;
        struct cli_cmd        *ourscli_cmd = NULL;
        int                   count    = 0;

        cmd = GF_CALLOC (1, sizeof (ourscli_cmds), cli_mt_cli_cmd);
        memcpy (cmd, ourscli_cmds, sizeof (ourscli_cmds));
        count = (sizeof (ourscli_cmds) / sizeof (struct cli_cmd));
        cli_cmd_sort (cmd, count);

        for (ourscli_cmd = cmd; ourscli_cmd->pattern; ourscli_cmd++)
                if (_gf_false == ourscli_cmd->disable)
                        cli_out ("%s - %s", ourscli_cmd->pattern, ourscli_cmd->desc);

        GF_FREE (cmd);
        return 0;
}

int
cli_cmd_ourscli_register (struct cli_state *state)
{
        int  ret = 0;
        struct cli_cmd *cmd = NULL;

        for (cmd = ourscli_cmds; cmd->pattern; cmd++) {

                ret = cli_cmd_register (&state->tree, cmd);
                if (ret)
                        goto out;
        }
out:
        return ret;
}
