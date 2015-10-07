%global _enable_debug_package 0
%global debug_package %{nil}

Summary:            Process watch utilities
Name:               pwatch
Version:            0.0.1-beta
Release:            1%{?dist}
License:            GPLv2+
Group:              Applications/System
Source:             pwatch-%{version}.tar.gz
URL:                https://github.com/orpiske/pwatch
BuildRequires:      cmake
BuildRequires:      make
BuildRequires:      gcc


%description
Process watching tools

%prep
%autosetup -n pwatch-%{version}

%build
cmake -DCMAKE_INSTALL_PREFIX=%{buildroot}/usr/local
make

%install
make install

%files
/usr/local

%changelog
* Wed Oct 07 2015 Otavio Rodolfo Piske <angusyoung@gmail.com> - 0.0.1
- Initial release
