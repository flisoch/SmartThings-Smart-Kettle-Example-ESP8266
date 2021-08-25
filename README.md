# Проект "Умный чайник"

## Что это
В этом репозитории содержится код прошивки esp8266 устройства "Умный чайник" с интерграцией в SmartThings. Создание этого проекта описано в [туториале](https://habr.com/ru/company/samsung/blog/573514/) на Хабре. Этот же пример, но с использованием esp32 и датчика температуры ds18B20 расположен в [этом репозитории](https://github.com/flisoch/SmartThings-Smart-Kettle-Example-esp32).
## Как начать
Если вы ещё не работали с SmartThings, рекомендую пройти [этот туториал](https://habr.com/ru/company/samsung/blog/489834/) на Хабре, в котором описаны шаги создания типового проекта в целом, и подготовка окружения, сборка и прошивка в частности. Та же эта информация доступна в [Getting Started](https://github.com/SmartThingsCommunity/st-device-sdk-c-ref/blob/master/doc/getting_started.md) справочного репозитория [st-device-sdk-ref-c](https://github.com/SmartThingsCommunity/st-device-sdk-c-ref) с примерами под разные платы.

### Сборка и прошивка примера
Если вы уже запускали примеры и у вас подготовлено окружение:

1. Перейдите в директорию `apps/esp8266` c примерами под эту платформу.
    ```
    st-device-sdk-c-ref
    ├── apps
    │   ├── ...
    │   ├── esp8266
    │   └── ...
    ├── ...
    ```
2. Находять в директории `apps/esp8266`, склонируйте этот репозиторий
 
   `$git clone https://github.com/flisoch/SmartThings-Smart-Kettle-Example-ESP8266.git`

3. Добавьте свои файлы `device_info.json` и `onboarding_config.json` в директорию `smart_kettle_example/main`

4. (Опционально). Создайте кастомное Heating Setpoint Capability по [алгоритму](https://github.com/flisoch/SmartThings-Smart-Kettle-Example-ESP8266/blob/master/custom-capability/README.md)

5. Перейдите обратно в директорию `st-device-sdk-c-ref` и соберите проект
   
   `$python3 build.py esp8266 smart_kettle_example`
   
6. Прошейте устройство и запустите вывод работы в терминал
   
   `$python3 build.py esp8266 smart_kettle_example flash monitor`
   
