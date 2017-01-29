/*
 *      fm-icon.h
 *
 *      Copyright 2009 Hong Jen Yee (PCMan) <pcman.tw@gmail.com>
 *      Copyright 2013 Andriy Grytsenko (LStranger) <andrej@rep.kiev.ua>
 *
 *      This file is a part of the Libfm library.
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2.1 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#ifndef __FM2_ICON_H__
#define __FM2_ICON_H__

#include "libfmqtglobals.h"
#include <gio/gio.h>
#include "gioptrs.h"
#include <memory>
#include <mutex>
#include <unordered_map>
#include <forward_list>
#include <QIcon>


namespace Fm2 {

class LIBFM_QT_API Icon {
public:

    explicit Icon() {}

    explicit Icon(const char* name);

    explicit Icon(const GIconPtr gicon);

    ~Icon();

    static std::shared_ptr<const Icon> fromName(const char* name);

    static std::shared_ptr<const Icon> fromGIcon(GObjectPtr<GIcon> gicon);

    static void unloadCache();

    GIconPtr gicon() const {
        return gicon_;
    }

    QIcon qicon() const;

    static QIcon qiconFromNames(const char* const* names);

    bool hasEmblems() const {
        return G_IS_EMBLEMED_ICON(gicon_.get());
    }

    std::forward_list<std::shared_ptr<const Icon>> emblems() const;

private:

    struct GIconHash {
        std::size_t operator()(GIcon* gicon) const {
            return g_icon_hash(gicon);
        }
    };

    struct GIconEqual {
        bool operator()(GIcon* gicon1, GIcon* gicon2) const {
            return g_icon_equal(gicon1, gicon2);
        }
    };

private:
    GIconPtr gicon_;
    mutable QIcon qicon_;

    static std::unordered_map<GIcon*, std::shared_ptr<Icon>, GIconHash, GIconEqual> cache_;
    static std::mutex mutex_;
};

} // namespace Fm2

Q_DECLARE_METATYPE(std::shared_ptr<const Fm2::Icon>)

#endif /* __FM2_ICON_H__ */
