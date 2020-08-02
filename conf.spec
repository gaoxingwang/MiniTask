Name:		TestConf
Version:	1.0.0
Release:	1%{?dist}
Summary:	TestConf-1.0.0

Group:		Applications/Productivity
License:	Freely redistributable without restriction
Source0:	TestConf-1.0.0.tar.gz

#BuildRequires:	
#Requires:	

%description
MiniTask Application

%prep
%setup -q


%build
make %{?_smp_mflags}


%install
install -d %{buildroot}/usr/bin/
install TestConf %{buildroot}/usr/bin/

%files
%{_bindir}



%changelog

