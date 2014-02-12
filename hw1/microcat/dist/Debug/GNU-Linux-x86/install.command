#!/bin/bash

# Exit the script as soon as any statement returns a non-zero exit code
set -e

# Tell bash to interpret line characters
IFS=$'\n'

# Subfolder structure under /Contents/Resources/
netbeans_subfolder='NetBeans/nb';

# Output info message
# $1 : Message
function info() {
	echo -e -n "\033[1;36m$1";
	de_colorize
}

# Output success message
# $1 : Message
function ok() {
	echo -e -n "\033[1;32m$1";
	de_colorize
}

# Output warning message
# $1 : Message
function warning() {
	echo -e -n "\033[1;33m$1";
	de_colorize
}

# Sets output color to default
function de_colorize() {
	echo -e -n '\033[00m';
}

# Installs the iconset
# $1 : Current Directory
# $2 : Netbeans Folder
function install_iconset() {
	sudo cp -f "$1/icons/netbeans.icns" "$2/";
	sudo cp -f "$1/icons/netbeans.icns" "$2/$netbeans_subfolder/";
	sudo cp -f "$1/icons/netbeans.png" "$2/$netbeans_subfolder/";
}

# Restores iconset
# $1 : Netbeans Folder
function restore_icons() {
	sudo mv -f "$1/netbeans_old.icns" "$1/netbeans.icns";
	sudo mv -f "$1/$netbeans_subfolder/netbeans_old.icns" "$1/$netbeans_subfolder/netbeans.icns";
	sudo mv -f "$1/$netbeans_subfolder/netbeans_old.png" "$1/$netbeans_subfolder/netbeans.png";
}

# Uninstalls the iconset
# $1 : Netbeans Folder
function remove_icons() {
	sudo rm -f "$1/netbeans.icns";
	sudo rm -f "$1/$netbeans_subfolder/netbeans.icns";
	sudo rm -f "$1/$netbeans_subfolder/netbeans.png";
}

# Creates a backup of the existing icons
# $1 : Netbeans Folder
function backup_icons() {
	sudo mv -f "$1/netbeans.icns" "$1/netbeans_old.icns";
	sudo mv -f "$1/$netbeans_subfolder/netbeans.icns" "$1/$netbeans_subfolder/netbeans_old.icns";
	sudo mv -f "$1/$netbeans_subfolder/netbeans.png" "$1/$netbeans_subfolder/netbeans_old.png";
}

#Entry point for file
function main() {
	# Get current working directory
	this_dir="$( cd -P "$( dirname "${BASH_SOURCE[0]}" )" && pwd )";

	# Iterate through versions
	versions=( $(find /Applications/NetBeans -iname "*.app") );

	# Clear screen for neat output
	clear;

	# Do version check
	for version in ${versions[*]}
	do
		#Netbeans location in Applications
	    netbeans_folder="$version/Contents/Resources";

		if [ -d "$netbeans_folder"  -a  -d "$netbeans_folder/$netbeans_subfolder/" ]; then

			# Check that old files don't already exist
			if [ ! -f "$netbeans_folder/netbeans_old.icns" -a ! -f "$netbeans_folder/$netbeans_subfolder/netbeans_old.icns" -a ! -f "$netbeans_folder/$netbeans_subfolder/netbeans_old.png" ]; then

				echo "Do you wish to install iconset for" $( info $version? );
				select yn in "Yes" "No"; do
					case $yn in
						Yes )
							backup_icons $netbeans_folder

							# Check if backup failed
							if [ ! $? -eq 0 ]; then
								echo "Could not back-up files, exiting" >&2
								exit;
							fi

							# Install new icons
							install_iconset $this_dir $netbeans_folder

							# Check if install failed
							if [ ! $? -eq 0 ]; then
								echo "Could not install files" >&2

								# Restore old icons
								restore_icons $netbeans_folder
								exit;
							fi

							ok "Installed Successfuly\n"

							break;;
						No )
							break;;
					esac
				done
			else

				echo "Previous iconset installation for $( warning $version ) detected, would you like to uninstall iconset or skip this version?";
				select yn in "Uninstall" "Skip"; do
					case $yn in
						Uninstall )
							# Remove old icons
							remove_icons $netbeans_folder

							# Restore old icons
							restore_icons $netbeans_folder
							ok "Uninstalled Successfuly\n"

							break;;
						Skip )
							break;;
					esac
				done
			fi
			echo "";
		fi
	done
}

#Initialise
main "$@"
