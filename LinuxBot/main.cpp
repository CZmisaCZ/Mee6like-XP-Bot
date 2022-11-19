#include <dpp/dpp.h>
//#include "include/dpp-10.0/dpp/dpp.h"

//#pragma warning(disable:4996)

const std::string    BOT_TOKEN = "MTAxMzcyOTk2ODI2NzczNTA4MA.GSCbqc.QvfAw-mae5Tl3ZXEXNNHvNgtLtwYNZ6kRozREA";
//official bot: "Nzc4NTY2Njk1Mjk1NjQ3NzU0.GJw2Dm.2RuSe8ztZU1kbBDLOB7zuMv0KbjOJdy4HKgrws";
//test bot: "MTAxMzcyOTk2ODI2NzczNTA4MA.GSCbqc.QvfAw-mae5Tl3ZXEXNNHvNgtLtwYNZ6kRozREA"

#include <string>
#include <stdio.h>
#include <time.h>

//////sleep for linux!!
//#include <unistd.h>
//unsigned int microsecond = 200000;//200ms

//////sleep for win!!
#include <chrono>
#include <thread>

// Calculate the current day of the week as an integer
//   now - Unix timestamp like that from time(NULL)
//   tz_offset - Number of hours off from UTC; i.e. PST = -8
//   Return value: Sunday=0, Monday=1, ... Saturday=6
int dayofweek(time_t now, int tz_offset) {
    // Calculate number of seconds since midnight 1 Jan 1970 local time
    time_t localtime = now + (tz_offset * 60 * 60);
    // Convert to number of days since 1 Jan 1970
    int days_since_epoch = localtime / 86400;
    // 1 Jan 1970 was a Thursday, so add 4 so Sunday is day 0, and mod 7
    int day_of_week = (days_since_epoch + 4) % 7;

    return day_of_week;
}
bool friday = false;


int main()
{
    /* Create bot cluster */
    dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

    /* Output simple log messages to stdout */
    bot.on_log(dpp::utility::cout_logger());

    /* Message handler to look for a command called !embed */
    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        if (event.msg.content == "!friday") {

            time_t now = time(NULL);
            if (dayofweek(now, +2) == 5)
            {
                if (friday == false)
                {
                    /* create the embed */
                    dpp::embed embed = dpp::embed().
                        set_color(dpp::colors::sti_blue).
                        set_title("***WHEN IT FRIDAY***").
                        set_url("https://youtu.be/_2U-0fAe-QQ").
                        //set_author("Some name", "https://dpp.dev/", "https://dpp.dev/DPP-Logo.png").
                        //set_description("Some description here").
                       //set_thumbnail("https://dpp.dev/DPP-Logo.png").

                        set_image("https://cdn.discordapp.com/attachments/656751148379668500/1013462947906994229/today-is.gif").
                        set_footer(dpp::embed_footer().set_text("gaming").set_icon("https://cdn.discordapp.com/attachments/656751148379668500/1013464958429839410/every_secon.gif")).
                        set_timestamp(time(0));

                    /* reply with the created embed */
                    bot.message_create(dpp::message(event.msg.channel_id, embed).set_reference(event.msg.id));
                    friday = true;
                }
                else
                {
                    /* create the embed */
                    dpp::embed embed = dpp::embed().
                        set_color(dpp::colors::rust).
                        set_title(":skull:").
                        set_description("someone already used !friday").
                        set_footer(dpp::embed_footer().set_text("gaming").set_icon("https://cdn.discordapp.com/attachments/656751148379668500/1013464958429839410/every_secon.gif")).
                        set_timestamp(time(0));

                    /* reply with the created embed */
                    bot.message_create(dpp::message(event.msg.channel_id, embed).set_reference(event.msg.id));
                }

            }
            else
            {
                time_t now = time(NULL);
                int localtim = dayofweek(now, +2);
                std::string desc;
                switch (localtim)
                {
                case 0:
                    desc = "5 days remain to friday";
                    break;
                case 1:
                    desc = "4 days remain to friday";
                    break;
                case 2:
                    desc = "3 days remain to friday";
                    break;
                case 3:
                    desc = "2 days remain to friday";
                    break;
                case 4:
                    desc = "1 days remain to friday";
                    break;
                case 6:
                    desc = "6 days remain to friday";
                    break;
                default:
                    break;
                }

                /* create the embed */
                dpp::embed embed = dpp::embed().
                    set_color(dpp::colors::rust).
                    set_title("there is no friday").


                    set_description(desc).

                    set_footer(dpp::embed_footer().set_text("gaming").set_icon("https://cdn.discordapp.com/attachments/656751148379668500/1013464958429839410/every_secon.gif")).
                    set_timestamp(time(0));

                /* reply with the created embed */
                bot.message_create(dpp::message(event.msg.channel_id, embed).set_reference(event.msg.id));
            }
        }
    if (event.msg.content == "!ping") {
        event.reply("Pong!");
    }
    //if (event.msg.content == "!day") {
    //    time_t now = time(NULL);
    //    const std::string s = "Current day of week: " + std::to_string(dayofweek(now, +2));
    //    event.reply(s);
    //}
        });

    /* Register slash command here in on_ready */
    bot.on_ready([&bot](const dpp::ready_t& event) {
        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
        }
        });


    /* Handle slash command */
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
        });



    /* Start the bot */
    bot.start(true);
    //bot.start(dpp::st_wait);


    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;


    while (true)
    {
        //////sleep for linux!!
        //usleep(microsecond);

        //////sleep for win!!
        sleep_for(250ms);

        if (friday == true)
        {
            time_t now = time(NULL);
            if (dayofweek(now, +2) != 5)
            {
                friday = false;
            }
        }
    };

    return 0;
}