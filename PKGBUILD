# PKGBUILD
pkgname=ModulusPlus
pkgver=1.0.1
pkgrel=1
pkgdesc="Modular arithmetic library for 256 bit unsigned integers"
arch=('x86_64')
url="https://github.com/thep0ntiff/ModulusPlus"
license=('MIT')
depends=()
makedepends=('gcc' 'make')
source=("$pkgname-$pkgver.tar.gz::https://github.com/thep0ntiff/ModulusPlus/archive/refs/tags/$pkgver.tar.gz")
sha256sums=('eef0d3af76349c270e59f771890b5904b111a860a527e44ada6967a0becd8df1')

build() {
    cd "$srcdir/$pkgname-$pkgver"
    make
}

package() {
    cd "$srcdir/ModulusPlus-$pkgver"
    make DESTDIR="$pkgdir" install
}
