# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.27
# 

Name:       harbour-ownkeepass

# >> macros
%define __provides_exclude_from ^%{_datadir}/.*$
%define __requires_exclude ^libgcrypt|libgpg-error|libc.*$
# << macros

%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}
Summary:    A password safe application
Version:    1.1.9
Release:    1
Group:      Qt/Qt
License:    GPL v2
Source0:    %{name}-%{version}.tar.bz2
Source100:  harbour-ownkeepass.yaml
Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(sailfishapp) >= 0.0.10
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(libgcrypt)

%description
ownKeepass is a password safe application for the Sailfish OS platform. You can use it to store your passwords for webpages, PINs, TANs and any other data that should be kept secret on your Jolla Smartphone. The database where that data is stored is encrypted using a master password.

%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
# << build pre

%qtc_qmake5  \
    VERSION=%{version}

%qtc_make %{?_smp_mflags}

# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%qmake5_install

# >> install post
# << install post

%files
%defattr(-,root,root,-)
%defattr(644,root,root,-)
/usr/share/icons/hicolor/86x86/apps
/usr/share/applications
/usr/share/harbour-ownkeepass
%attr(655,-,-) %{_bindir}
# >> files
# << files
