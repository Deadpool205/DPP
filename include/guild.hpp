#pragma once
#include "assets.hpp"
#include "channel.hpp"
#include "nlohmann/json.hpp"
#include "object.hpp"

#include "boost/date_time/posix_time/posix_time.hpp"

namespace discord {

    typedef int64_t snowflake;

    class Role;
    class Color;
    class Emoji;
    class Member;
    struct AuditLogs;
    class Integration;

    class Guild : public Object {
    public:
        struct VoiceRegion {
            /**
            * @brief Struct that represents a voice region
            */
            std::string id;   /**< Id of the voice region */
            std::string name; /**< Name of the voice region */
            bool vip;         /**< Whether or not this voice region is VIP server only */
            bool optimal;     /**< Whether this is the optimal voice region for your bot instance */
            bool deprecated;  /**< Whether this voice region is deprecated */
            bool custom;      /**< Whether this is a custom voice region */
        };

        Guild() = default;
        Guild(snowflake);

        Guild(nlohmann::json const);
        Guild& update(nlohmann::json const);

        pplx::task<void> edit(std::string const&, std::string const& = "", int = -1, int = -1, int = -1, snowflake = -1, int = -1, std::string const& = "", snowflake = -1, std::string const& = "", snowflake = -1);
        pplx::task<void> remove();
        pplx::task<std::vector<discord::Channel>> get_channels();
        pplx::task<discord::Channel> create_channel(std::string const&, bool, int = -1, std::string const& = "", int = -1, int = -1, int = -1, int = -1, std::vector<discord::PermissionOverwrites> const& = {}, snowflake = -1);

        pplx::task<discord::Member> get_member(snowflake);
        pplx::task<std::vector<discord::Member>> get_members(int, snowflake = 0);
        pplx::task<void> add_member(nlohmann::json const&, snowflake);

        pplx::task<void> edit_bot_username(std::string const&);
        pplx::task<AuditLogs> get_audit_logs();
        pplx::task<std::vector<std::pair<std::string, discord::User>>> get_bans();
        pplx::task<std::pair<std::string, discord::User>> get_ban(discord::Object const&);

        pplx::task<void> unban(discord::Object const&);

        pplx::task<discord::Emoji> create_emoji(std::string const&, discord::Emoji&, std::vector<discord::Role> = {});

        pplx::task<std::vector<discord::Role>> get_roles();

        pplx::task<discord::Role> create_role(std::string const&, PermissionOverwrites&, discord::Color, bool, bool);

        pplx::task<int> get_prune_count(int);
        pplx::task<int> begin_prune(int, bool);

        pplx::task<std::vector<VoiceRegion>> get_voice_regions();
        pplx::task<std::vector<discord::Invite>> get_invites();

        pplx::task<snowflake> get_embed();
        pplx::task<snowflake> edit_embed(snowflake = -1);

        pplx::task<std::string> get_vanity_invite_url();

        discord::Asset get_widget_image(std::string const&);
        pplx::task<std::vector<discord::Integration>> get_integrations();
        pplx::task<void> create_integration(discord::Integration const&);
        pplx::task<void> edit_integration(discord::Integration const&, int, int, bool);
        pplx::task<void> remove_integration(discord::Integration const&);
        pplx::task<void> sync_integration(discord::Integration const&);

    public:
        int mfa_level;
        int afk_timeout;
        int member_count;
        int verification_level;
        int explicit_content_filter;

        bool large;
        bool unavailable;

        snowflake application_id;

        std::string name;
        std::string region;
        discord::Asset icon;
        discord::Asset banner;
        discord::Asset splash;
        boost::posix_time::ptime created_at{};
        std::string vanity_url_code;

        std::vector<int> features;
        std::vector<std::shared_ptr<discord::Role>> roles;
        std::vector<discord::Emoji> emojis;

        std::vector<std::shared_ptr<discord::Member>> members;
        std::vector<std::shared_ptr<discord::Channel>> channels;

        std::shared_ptr<discord::Member> owner;
        discord::Channel afk_channel;
        discord::Channel system_channel;

        pplx::task<std::vector<discord::Webhook>> get_webhooks();
        pplx::task<void> leave();

        pplx::task<std::vector<discord::Emoji>> list_emojis();
        pplx::task<discord::Emoji> get_emoji(discord::Emoji const&);
        pplx::task<discord::Emoji> edit_emoji(discord::Emoji const&, std::string, std::vector<discord::Role> = {});
        pplx::task<void> remove_emoji(discord::Emoji const&);
    };
}  // namespace discord