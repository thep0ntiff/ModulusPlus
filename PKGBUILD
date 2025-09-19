# PKGBUILD
pkgname=ModulusPlus
pkgver=1.0.2
pkgrel=1
pkgdesc="Modular arithmetic library for 256 bit unsigned integers"
arch=('x86_64')
url="https://github.com/thep0ntiff/ModulusPlus"
license=('MIT')
depends=()
makedepends=('gcc' 'make')
source=("$pkgname-$pkgver.tar.gz::https://github.com/thep0ntiff/ModulusPlus/archive/refs/tags/v$pkgver.tar.gz")
sha256sums=('2a2cc3c5969fa95214c575f29a4fa5e8b8d9a86c6c73a7ad92a45ad5789059ef')

build() {
    cd "$srcdir/$pkgname-$pkgver"
    make
}

package() {
    cd "$srcdir/ModulusPlus-$pkgver"
    make DESTDIR="$pkgdir" install
}
