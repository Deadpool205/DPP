#include "user.hpp"
#include "utils.hpp"
#include "channel.hpp"
#include "bot.hpp"


discord::User::User(snowflake id)
    : discord::Object(id) {
    auto user = discord::utils::get(discord::detail::bot_instance->users, [id](auto const& usr) {
        return usr->id == id;
    });
    if (user) {
        *this = *user;
    }
}

discord::User::User(nlohmann::json const j)
    : discord::Object(to_sf(j["id"])) {
    bot = j.contains("bot");
    discriminator = j["discriminator"];
    if (j.contains("avatar")) {
        if (j["avatar"].is_null()) {
            avatar = { "", default_user_avatar, false, to_sf(discriminator) };
        } else {
            std::string av_hash = j["avatar"];
            avatar = { av_hash, user_avatar, av_hash[0] == 'a' && av_hash[1] == '_', id };
        }
    }
    name = j["username"];
    mention = "<@" + std::to_string(id) + ">";
}

discord::User& discord::User::update(nlohmann::json const data) {
    update_object_bulk(data,
                       "bot", bot,
                       "discriminator", discriminator,
                       "id", id,
                       "username", name);

    if (data.contains("avatar")) {
        if (data["avatar"].is_null()) {
            avatar = { "", default_user_avatar, false, to_sf(discriminator) };
        } else {
            std::string av_hash = data["avatar"];
            avatar = { av_hash, user_avatar, av_hash[0] == 'a' && av_hash[1] == '_', id };
        }
    }

    mention = "<@" + std::to_string(id) + ">";
    return *this;
}

pplx::task<discord::Channel> discord::User::create_dm() {
    return send_request(methods::POST,
                        endpoint("/users/@me/channels"),
                        0, global,
                        nlohmann::json({ { "recipient_id", id } }))
        .then([](pplx::task<Result<nlohmann::json>> const& resp) {
            return discord::Channel{
                resp.get().unwrap()
            };
        });
}
