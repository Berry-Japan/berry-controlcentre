%define name berry-controlcentre
%define version 0.03
%define release b1

Name:		%{name}
Summary:	Control Centre for Berry Linux
Version:	%{version}
Release:	%{release}
License:	GPL
Group:		System/Tools
Source:		%{name}-%{version}.tar.bz2
Buildroot:	%{_tmppath}/%{name}-%{version}

BuildArchitectures: i586


%description
Control Centre for Berry Linux


##
## Setup Section
##

%prep
%setup -q


##
## Build Section
##

%build
qmake
make


##
## Install Section
##

%install
mkdir -p %{buildroot}/opt/berry
strip BerryCC
install -m 755 BerryCC %{buildroot}/opt/berry/

mkdir -p %{buildroot}/usr/share/applications/Berry
install -m 644 *.desktop %{buildroot}/usr/share/applications/Berry


##
## Clean Section
##

%clean
[ -n "%{buildroot}" -a "%{buildroot}" != / ] && rm -rf %{buildroot}
rm -rf $RPM_BUILD_DIR/%{name}-%{version}


##
## Files Section
##

%files
%defattr (-,root,root)
/opt/berry/*
/usr/share/applications/Berry/*.desktop


##
## change log
##

%changelog
* Wed Aug 31 2005 Yuichiro Nakada <berry@po.yui.mine.nu>
- Create for Berry Linux
