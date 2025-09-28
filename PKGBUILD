# PKGBUILD
pkgname=ModulusPlus
pkgver=1.0.5
pkgrel=1
pkgdesc="Modular arithmetic library for 256 bit unsigned integers"
arch=('x86_64')
url="https://github.com/thep0ntiff/ModulusPlus"
license=('MIT')
depends=()
makedepends=('gcc' 'make')
source=("$pkgname-$pkgver.tar.gz::https://github.com/thep0ntiff/ModulusPlus/archive/refs/tags/v$pkgver.tar.gz")
sha256sums=('45e697c10e866c1f524ba77618b6577099f0a753dcb1801abd3e6e6cd8d22116')

build() {
    cd "$srcdir/$pkgname-$pkgver"
    make
}

package() {
    cd "$srcdir/ModulusPlus-$pkgver"
    make DESTDIR="$pkgdir" install
}
