<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="ru_RU">
<context>
    <name>QObject</name>
    <message>
        <source>There is nothing to generate, diagram doesn&apos;t have Initial Node</source>
        <translation type="obsolete">Генерация невозможна, на диаграмме нет начальных блоков</translation>
    </message>
    <message>
        <location filename="nxtOSEK/generators/ifElementGenerator.cpp" line="46"/>
        <source>If block has no 2 correct branches!May be you need to connect one of them to some diagram element.</source>
        <translation></translation>
    </message>
    <message>
        <location filename="nxtOSEK/generators/ifElementGenerator.cpp" line="101"/>
        <source>Link has no object on its end. May be you need to connect it to diagram object.</source>
        <translation>Одна из связей прикреплена только к одному блоку. Пожалуйста, проверьте правильность расстановки связей.</translation>
    </message>
    <message>
        <location filename="nxtOSEK/generators/ifElementGenerator.cpp" line="168"/>
        <location filename="nxtOSEK/generators/ifElementGenerator.cpp" line="175"/>
        <source>If block has no 2 correct branches! May be you need to connect one of them to some diagram element.</source>
        <translation>Из блока &quot;Условие&quot; должны исходить две связи. Пожалуйста, проверьте правильность диаграммы.</translation>
    </message>
    <message>
        <location filename="nxtOSEK/generators/ifElementGenerator.cpp" line="211"/>
        <source>This diagram isn&apos;t structed diagram, because there are IF block with 2 back arrows!</source>
        <translation>Диаграмма составлена неверно. У блока &quot;Условие&quot; присутствуют  две исходящие непомеченные связи!</translation>
    </message>
    <message>
        <location filename="nxtOSEK/generators/ifElementGenerator.cpp" line="215"/>
        <source>Generator JUST does not work in this case.</source>
        <translation>Генератор просто не работает в этом случае.</translation>
    </message>
    <message>
        <location filename="nxtOSEK/generators/loopElementGenerator.cpp" line="33"/>
        <source>Loop block has no correct loop branch! May be you need to connect it to some diagram element.</source>
        <translation>У блока &quot;Цикл&quot; не образован правильный цикл. Пожалуйста, прикрепите связь, помеченную как итерация, к какому-нибудь блоку диаграммы.</translation>
    </message>
    <message>
        <location filename="nxtOSEK/generators/loopElementGenerator.cpp" line="51"/>
        <source>Loop block has no correct next block branch! May be you need to connect it to some diagram element.</source>
        <translation>У блока &quot;Цикл&quot; не найдена ветвь, выполняющаяся после цикла. Пожалуйста, соедините блок с каким-нибудь элементом диаграммы.</translation>
    </message>
    <message>
        <location filename="nxtOSEK/generators/simpleElementGenerator.cpp" line="32"/>
        <source>Element has no correct next element because its link has no end object. May be you need to connect it to diagram object.</source>
        <translation>Одна из связей прикреплена только к одному блоку.</translation>
    </message>
    <message>
        <location filename="nxtOSEK/generators/simpleElementGenerator.cpp" line="48"/>
        <source>There is no outgoing connected element with no final node!</source>
        <translation>Генерация невозможна, нет исходящей связи, соединенной с концом диаграммы!</translation>
    </message>
    <message>
        <location filename="nxtOSEK/generators/simpleElementGenerator.cpp" line="75"/>
        <source>There are more than 1 outgoing connected elements with simple robot element!</source>
        <translation>На диаграмме присутствуют лишние связи. Пожалуйста, проверьте правильность расстановки связей!</translation>
    </message>
    <message>
        <location filename="nxtOSEK/generators/simpleElements/initialBlockGenerator.cpp" line="46"/>
        <location filename="nxtOSEK/generators/simpleElements/waitForColorBlockGenerator.cpp" line="18"/>
        <location filename="nxtOSEK/generators/simpleElements/waitForColorIntensityBlockGenerator.cpp" line="18"/>
        <source>NXTOsek doesn&apos;t support color sensor</source>
        <translation>NXTOsek не поддерживает сенсор цвета</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtOSEKRobotGenerator.cpp" line="113"/>
        <source>There is nothing to generate, diagram doesn&apos;t have Initial Node or Initial Block</source>
        <translation>Генерация невозможна. На диаграмме нет начального блока</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtOSEKRobotGenerator.cpp" line="166"/>
        <source>There is no opened diagram</source>
        <translation>Нет открытой диаграммы</translation>
    </message>
</context>
<context>
    <name>robots::generator::NxtFlashTool</name>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="41"/>
        <source>Firmware flash started. Please don&apos;t disconnect robot during the process</source>
        <translation>Начат процесс загрузки прошивки в робота. Пожалуйста, не отсоединяйте робота, пока процесс не будет завершен</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="47"/>
        <source>Some error occured. Make sure you are running QReal with superuser privileges</source>
        <translation>Ошибка. Убедитесь, что QReal:Robots запущен с правами администратора</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="55"/>
        <source>Flashing process completed.</source>
        <translation>Процесс загрузки программы завершен.</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="57"/>
        <source>flash.sh not found. Make sure it is present in QReal installation directory</source>
        <translation>Не найден скрипт flash.sh. Убедитесь, что пакет nxt-tools установлен корректно</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="59"/>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="101"/>
        <source>QReal requires superuser privileges to flash NXT robot</source>
        <translation>Для загрузки прошивки в робота требуется запустить QReal:Robots с правами администратора</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="72"/>
        <source>NXT not found. Check USB connection and make sure the robot is ON</source>
        <translation>Соединение с роботом не обнаружено. Проверьте USB-соединение и убедитесь, что робот включен</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="74"/>
        <source>NXT is not in reset mode. Please reset your NXT manually and try again</source>
        <translation>Робот находится в неправильном режиме. Переведите робота в режим перепрошивки</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="76"/>
        <source>Firmware flash complete!</source>
        <translation>Процесс загрузки прошивки в робота завершен!</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="91"/>
        <source>Uploading program started. Please don&apos;t disconnect robot during the process</source>
        <translation>Начат процесс загрузки программы в робота. Пожалуйста, не отсоединяйте робота, пока процесс не будет завершен</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="99"/>
        <source>Uploading failed. Make sure that X-server allows root to run GUI applications</source>
        <translation>Не удалось загрузить программу в робота. Убедитесь, что QReal:Robots запущен с нужными правами</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="129"/>
        <source>Could not upload program. Make sure the robot is connected and ON</source>
        <translation>Не удалось загрузить программу в робота. Убедитесь, что робот включен и подсоединен к компьютеру</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="131"/>
        <source>Uploading completed successfully</source>
        <translation>Загрузка программы завершена успешно</translation>
    </message>
    <message>
        <location filename="nxtOSEK/nxtFlashTool.cpp" line="136"/>
        <source>QReal requires superuser privileges to upload programs on NXT robot</source>
        <translation>Для загрузки программ в робота требуется запустить QReal:Robots с правами администратора</translation>
    </message>
</context>
<context>
    <name>robots::generator::RobotsGeneratorPlugin</name>
    <message>
        <location filename="robotsGeneratorPlugin.cpp" line="38"/>
        <source>Generate code</source>
        <translation>Генерировать код</translation>
    </message>
    <message>
        <location filename="robotsGeneratorPlugin.cpp" line="42"/>
        <source>Flash robot</source>
        <translation>Прошить</translation>
    </message>
    <message>
        <location filename="robotsGeneratorPlugin.cpp" line="46"/>
        <source>Upload program</source>
        <translation>Загрузить программу</translation>
    </message>
    <message>
        <location filename="robotsGeneratorPlugin.cpp" line="96"/>
        <source>flash.sh not found. Make sure it is present in QReal installation directory</source>
        <translation>Не найден скрипт flash.sh. Убедитесь, что пакет nxt-tools установлен корректно</translation>
    </message>
    <message>
        <location filename="robotsGeneratorPlugin.cpp" line="105"/>
        <source>upload.sh not found. Make sure it is present in QReal installation directory</source>
        <translation>Не найден скрипт upload.sh. Убедитесь, что пакет nxt-tools установлен корректно</translation>
    </message>
</context>
</TS>
