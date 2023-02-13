//
// Created by user on 20.05.2022.
//

#ifndef FLAZER_LOGIN_H
#define FLAZER_LOGIN_H

//#include <boost/algorithm/string/classification.hpp>
//#include <boost/algorithm/string/split.hpp>
#include <packets/binary/BinaryStream.h>
#include <packets/simplePackets/info.h>
#include <jwtcpp/nlohmann/json.hpp>
#include <jwtcpp/jwt-cpp/traits/nlohmann-json/traits.h>
#include <range/v3/range.hpp>
#include <range/v3/view/split.hpp>

struct cLoginData {
    char *pubkey;
    char *identity;
    char *gameVersion;
    char *skinData;
    char *skinID;
    char *tenantID;
    char *serverAddress;
    char *languageCode;
    char *deviceModel;
    char *username;
    int* deviceOS;
    int* UIProfile;
    int* ADRole;
    int* GUIScale;
    int* currentInputMode;
    int* defaultInputMode;
    uint8_t* gameEdition;
    int32_t* protocol;
    long long int* clientRandomID;
};

class login {
public:
    int32_t protocol{};
    u_char gameEdition{};
    std::string pubkey;
    std::string identity;
    std::string gameVersion;
    std::string skinData;
    std::string skinID;
    std::string tenantID;
    int deviceOS{};
    int UIProfile{};
    int ADRole{};
    int GUIScale{};
    long long int clientRandomID{};
    int currentInputMode{};
    int defaultInputMode{};
    std::string serverAddress;
    std::string languageCode;
    std::string deviceModel;
    std::string username;

    explicit login(BinaryStream& stream) : stream(stream){};

    std::vector<std::string> encode(const std::string& pubt) {
        stream.reset();
        stream.putByte((unsigned char) protoInfo::LOGIN);
		stream.swapEndianness();
        stream.putSInt(protocol); //todo check if big endian
		stream.swapEndianness();
        stream.putByte(gameEdition);

        return makeRequest(pubt);
        //stream.putString(request);
    }

    void decode() {
		stream.swapEndianness();
        protocol = stream.getSInt();
		stream.swapEndianness();
        gameEdition = stream.getByte();
        request = stream.getString();

        parse();
    }

   // [[nodiscard]] auto clone() const -> std::unique_ptr<dataPacket> override {return std::unique_ptr<dataPacket>(new login{*this});}

   // ~login() override = default;

    std::tuple<std::string, short> getProxyAddress() {
        auto words = serverAddress | ranges::views::split(':') | ranges::to<std::vector<std::string>>();
        return {words.at(0), (short) std::stoi(words.at(1))};
    }

    void parse() {
        stream.reset();
        stream.put(request);
        auto chain = stream.get(stream.getSInt());
        chain = nlohmann::json::parse(chain)["chain"][0].get<std::string>();
        auto decoded = jwt::decode(chain).get_payload_claims();
        pubkey = decoded["identityPublicKey"].as_string();
        auto extra = decoded["extraData"].to_json();
        username = extra.get("displayName").to_str();
        identity = extra.get("identity").to_str();

        chain = stream.get(stream.getSInt());
        decoded = jwt::decode(chain).get_payload_claims();

        currentInputMode = (int) decoded["CurrentInputMode"].as_int();
        clientRandomID = decoded["ClientRandomId"].as_int();
        defaultInputMode = (int) decoded["DefaultInputMode"].as_int();
        UIProfile = (int) decoded["UIProfile"].as_int();
        GUIScale = (int) decoded["GuiScale"].as_int();
        skinData = decoded["SkinData"].as_string();
        serverAddress = decoded["ServerAddress"].as_string();
        ADRole = (int) decoded["ADRole"].as_int();
        deviceOS = (int) decoded["DeviceOS"].as_int();
        languageCode = decoded["LanguageCode"].as_string();
        deviceModel = decoded["DeviceModel"].as_string();
        gameVersion = decoded["GameVersion"].as_string();
        skinID = decoded["SkinId"].as_string();
        tenantID = decoded["TenantId"].as_string();
    }

    cLoginData *makeCLogin() {
        return new cLoginData{
                .pubkey = pubkey.data(),
                .identity =  identity.data(),
                .gameVersion = gameVersion.data(),
                .skinData = skinData.data(),
                .skinID =  skinID.data(),
                .tenantID = tenantID.data(),
                .serverAddress =  serverAddress.data(),
                .languageCode = languageCode.data(),
                .deviceModel =  deviceModel.data(),
                .username =  username.data(),
                .deviceOS = new int(deviceOS),
                .UIProfile = new int(UIProfile),
                .ADRole = new int(ADRole),
                .GUIScale = new int(GUIScale),
                .currentInputMode = new int(currentInputMode),
                .defaultInputMode = new int(defaultInputMode),
                .gameEdition = new unsigned char(gameEdition),
                .protocol = new int(protocol),
                .clientRandomID = new long long int(clientRandomID),
        };
    }

    void fromCLogin(cLoginData *data) {
        protocol = *data->protocol;
        gameEdition = *data->gameEdition;
        pubkey = std::string(data->pubkey);
        identity = std::string(data->identity);
        gameVersion = std::string(data->gameVersion);
        skinData = std::string(data->skinData);
        skinID = std::string(data->skinID);
        tenantID = std::string(data->tenantID);
        ADRole = *data->ADRole;
        deviceOS = *data->deviceOS;
        UIProfile = *data->UIProfile;
        GUIScale = *data->GUIScale;
        clientRandomID = *data->clientRandomID;
        currentInputMode = *data->currentInputMode;
        defaultInputMode = *data->defaultInputMode;
        serverAddress = std::string(data->serverAddress);
        languageCode = std::string(data->languageCode);
        deviceModel = std::string(data->deviceModel);
        username = std::string(data->username);
    }


private:
    BinaryStream& stream;
    std::string request;

    std::vector<std::string> makeRequest(const std::string& pubt) {
        BinaryStream chainStream;
        nlohmann::json j;
        auto identityChain = std::map<std::string, std::vector<std::string>>{
                {"chain",
                 std::vector<std::string>{jwt::create<jwt::traits::nlohmann_json>()
                                                  .set_not_before(std::chrono::system_clock::now() -
                                                                  std::chrono::seconds{4912}) //todo check client
                                                  .set_expires_at(std::chrono::system_clock::now() +
                                                                  std::chrono::seconds{31531089})
                                                  .set_payload_claim("extraData", nlohmann::json{
                                                          {"displayName", username},
                                                          {"identity",    identity}
                                                  })
                                                  .set_payload_claim("identityPublicKey", pubt)
                                                  .set_header_claim("x5u", pubt)
                                                  .sign(jwt::algorithm::es384(pubt, ""))
                 }}
        };
        j = identityChain;
        auto dataChain = jwt::create<jwt::traits::nlohmann_json>()
                .set_payload_claim("CurrentInputMode", currentInputMode)
                .set_payload_claim("DefaultInputMode", defaultInputMode)
                .set_payload_claim("ClientRandomId", clientRandomID)
                .set_payload_claim("UIProfile", UIProfile)
                .set_payload_claim("GuiScale", GUIScale)
                .set_payload_claim("SkinData", skinData)
                .set_payload_claim("SkinId", skinID)
             //   .set_payload_claim("SkinId", skinID)
                .set_payload_claim("ServerAddress", serverAddress)
                .set_payload_claim("LanguageCode", languageCode)
                .set_payload_claim("DeviceModel", deviceModel)
                .set_payload_claim("GameVersion", gameVersion)
                .set_payload_claim("TenantId", tenantID)
                .set_payload_claim("ADRole", ADRole)
                .set_payload_claim("DeviceOS", deviceOS)
                .set_header_claim("x5u", pubt)
                .sign(jwt::algorithm::es384(pubt, ""));
                
        std::vector<std::string> out{j, dataChain};

        return out;
    }
};


//todo obfuscate keys
#endif //FLAZER_LOGIN_H
