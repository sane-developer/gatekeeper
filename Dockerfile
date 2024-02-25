FROM centos:latest

RUN yum -y install epel-release && \
    yum -y install 389-ds-base

EXPOSE 389 636

ENV DS_DM_PASSWORD=password
ENV DS_ADMIN_USERNAME=admin
ENV DS_ADMIN_PASSWORD=admin

COPY resources/setup-ds-admin.pl /usr/local/bin/

RUN setup-ds-admin.pl --silent --general.FullMachineName=localhost --admin.AdminDomain=localhost --base.AdminDomain=localhost --silent-mode --admin.AdministratorDN="cn=Directory Manager" --admin.AdminPassword=$DS_ADMIN_PASSWORD --admin.SuiteSpotUserID=dirsrv --admin.SuiteSpotGroup=dirsrv

CMD ["/usr/sbin/ns-slapd", "-D", "/etc/dirsrv/slapd-instance"]

HEALTHCHECK CMD ["/bin/bash", "-c", "ldapsearch -x -D 'cn=Directory Manager' -w $DS_ADMIN_PASSWORD -b 'cn=config' '(objectclass=*)'"]
