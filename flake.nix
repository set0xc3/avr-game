{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = {nixpkgs, ...}: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    devShells.${system}.default = pkgs.mkShell {
      buildInputs = [
        pkgs.avrdude
        pkgs.bear
        pkgs.pkgsCross.avr.buildPackages.gcc
      ];

      AVR_PATH = "${pkgs.pkgsCross.avr.libcCross}/avr";
    };
  };
}
