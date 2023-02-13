#pragma once
#include <string>

namespace minecraft {
    namespace api {

        class Api {

        public:

            void** vtable;
            std::string envPath;
            void** playerIfaceVtable;
            void** networkIfaceVtable;

        };

    }
}