/** \file
 *  \brief 本地化支持.
 *  \sa N1570 §7.11 Localization <locale.h>.
 *  \sa [locale.h](http://en.cppreference.com/w/c/locale)
 *  \author zhengrr
 *  \date 2016-11-7
 *  \copyright The MIT License
 */
#include <locale.h>

/** \brief 默认 setlocale.
 *  \details 任何 C 程序执行开始时隐含调用的 setlocale.
 */
static void default_setlocale(void)
{
        setlocale(LC_ALL, "C");
}

/** \brief 本地 setlocale.
 *  \details 不指定地区, 由程序自行判断本地地区的 setlocale.
 */
static void native_setlocale(void)
{
        setlocale(LC_ALL, "");
}

/** \brief setlocale 函数.
 *  \details
 *  \param category 指定的类别, 选用 locale.h 中定义的宏.
 *  \param locale 指定的地区, 若为空指针, 则查询当前配置并返回.
 *  \return 若成功, 返回相关地区字串; 若失败, 返回空指针.
 *  \sa <http://en.cppreference.com/w/c/locale/setlocale>
 */
static char *setlocale_info(int category, const char *locale)
{
        return setlocale(category, locale);
}
