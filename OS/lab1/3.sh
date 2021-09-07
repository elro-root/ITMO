#!/bin/bash
#3. Создать текстовое меню с 4 пунктами. При вводе пользователем номера пункта меню происходит запуск редактора nano, редактора vi, браузера links или выход из меню
echo "Выберите действие:"
echo "1 = nano"
echo "2 = vi"
echo "3 = links"
echo "4 = exit"
read a
case $a in
1 )
/usr/bin/nano
;;
2 )
/usr/bin/vim
;;
3 )
/usr/local/bin/links
;;
4 )
echo "Goodbye"
exit 0
;;
esac


