#!/bin/bash
cd "`dirname "$0"`"
echo "Script to create construir package"
mkdir -p pkgs
if [ ! -f pkgs/libbobcat-3.14.00-1-x86_64.pkg.tar.xz ]; then
    echo "You need to download"
    echo 'https://mega.co.nz/#F!9kVTBZCK!CQQskU8DhcBOo67EQ2UaWw'
    echo "and place is in pkgs"
    exit 1
fi

for pkg in boost-1.53.0-2-x86_64.pkg.tar.xz boost-libs-1.53.0-2-x86_64.pkg.tar.xz kbproto-1.0.6-1-any.pkg.tar.xz libbobcat-3.14.00-1-x86_64.pkg.tar.xz libx11-1.6.0-1-x86_64.pkg.tar.xz libxau-1.0.8-1-x86_64.pkg.tar.xz libxcb-1.9.1-1-x86_64.pkg.tar.xz libxdmcp-1.1.1-1-x86_64.pkg.tar.xz xcb-proto-1.8-1-any.pkg.tar.xz xproto-7.0.24-1-any.pkg.tar.xz; do
    if [ ! -f "pkgs/$pkg" ]; then
        echo "Required package $pkg"
        echo "not found"
        exit 1
    fi
done

tar -cJf ../ccbuild-HEAD-construir_i1.tar.xz --exclude=.git --transform 's/^ccbuild/job/' ../ccbuild
echo "Created ../ccbuild-HEAD_i1.tar.xz"






