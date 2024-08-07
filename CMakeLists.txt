cmake_minimum_required(VERSION 3.16)

project(currencyApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(cryptoCurrencyApp
    src/main.cpp
)
target_include_directories(cryptoCurrencyApp PRIVATE "src" "qml")

qt_add_qml_module(cryptoCurrencyApp
    URI currencyApp
    VERSION 1.0
        SOURCES src/cryptocurrencymodel.h src/cryptocurrencymodel.cpp
        SOURCES src/appcontroller.h src/appcontroller.cpp
        SOURCES src/cryptocurrency.h src/cryptocurrency.cpp
        SOURCES src/cryptocurrencyproxymodel.h src/cryptocurrencyproxymodel.cpp
        SOURCES src/coingeckodataworker.h src/coingeckodataworker.cpp
    QML_FILES
        qml/Main.qml
        QML_FILES qml/NavigationBar.qml
        QML_FILES qml/LoadingScreen.qml
        QML_FILES qml/CurrencyDelegate.qml
)

qt_add_resources(cryptoCurrencyApp "images"
    FILES images/loading_indicator.png)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(cryptoCurrencyApp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.cryptoCurrencyApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(cryptoCurrencyApp
    PRIVATE Qt6::Quick Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS cryptoCurrencyApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
