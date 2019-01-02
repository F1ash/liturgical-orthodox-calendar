#include <QString>

QString SCRIPT = QString::fromUtf8("<html><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" /><style> form.fixed { position: fixed; background-color: rgba(255, 255, 255, 0.75); top: 0px; left: 5px; z-index: 999; } #top { position: relative; top: 45px; } </style><body background=\"%1\" >%2<h3 id =\"top\" align=\"center\"><font color=\"red\">ПРАВОСЛАВНЫЙ КАЛЕНДАРЬ</font></h3> <div id =\"top\" align=\"center\">");
QString SCRIPT1 = QString::fromUtf8("</div> <div id =\"top\" ><script language=\"Javascript\"> var d=new Date(); var to=-4-d.getTimezoneOffset()/60; document.write ( '<script language=\"Javascript\" src=\"http://script.pravoslavie.ru/calendar.php?tmshift='+to +'");
QString SCRIPT2 = QString::fromUtf8("\"><\\/script>');</script></br>");
QString SCRIPT3 = QString::fromUtf8("</div></body></html>");

QString LITURGY = QString::fromUtf8("<div class=\"sluzh\"><a href=\"http://www.patriarchia.ru/bu/%1/print.html\">Богослужебные указания</a>");

QString SEARCH = QString::fromUtf8("<form class=\"fixed\" action=\"http://www.hristianstvo.ru/search\" target=\"_self\" id=\"cse-search-box-iskomoe\"><div><span style=\"font-size:10pt\">Поиск в православном интернете:</span><br><input type=\"text\" name=\"q\" size=\"32\" /><input type=\"image\" name=\"i\" src=\"/usr/share/icons/oxygen/base/16x16/actions/zoom-next.png\" /><input type=\"hidden\" name=\"firefox-a\" value=\"UTF-8\" /><input type=\"hidden\" name=\"cx\" value=\"006620037580445780645:e4joz-0lovc\" /><input type=\"hidden\" name=\"cof\" value=\"FORID:11\" /><input type=\"hidden\" name=\"newwindow\" value=\"1\" /><input type=\"hidden\" name=\"where\" value=\"2\" /><input type=\"hidden\" name=\"hl\" value=\"ru\" /><input type=\"hidden\" name=\"lr\" value=\"lang_ru\" /><input type=\"hidden\" name=\"source\" value=\"blog\" /></div></form><script type=\"text/javascript\" src=\"http://www.google.com/coop/cse/brand?form=cse-search-box-iskomoe&lang=ru\"></script>");
