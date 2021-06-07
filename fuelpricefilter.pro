QT += widgets network
requires(qtConfig(combobox))

HEADERS     = window.h
SOURCES     = main.cpp \
              window.cpp

# install
target.path = ./build/
INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android

    ANDROID_EXTRA_LIBS = \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/arm/libcrypto_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/arm/libssl_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/x86/libcrypto_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/x86/libssl_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/x86_64/libcrypto_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/x86_64/libssl_1_1.so \
        C:/qt_projects/fuelpricefilter/../../Users/fengy/AppData/Local/Android/Sdk/android_openssl/latest/arm64/libcrypto_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/arm/libcrypto_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/arm/libssl_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/arm64/libcrypto_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/arm64/libssl_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/x86/libcrypto_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/x86/libssl_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/x86_64/libcrypto_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/x86_64/libssl_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/arm/libcrypto_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/arm/libssl_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/arm64/libcrypto_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/arm64/libssl_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/x86/libcrypto_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/x86/libssl_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/x86_64/libcrypto_1_1.so \
        C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/no-asm/latest/x86_64/libssl_1_1.so \
        $$PWD/../../Users/fengy/AppData/Local/Android/Sdk/android_openssl/latest/arm64/libcrypto_1_1.so
}
android: include(C:/Users/fengy/AppData/Local/Android/Sdk/android_openssl/openssl.pri)
