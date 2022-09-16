#!/bin/bash

# error handling
if ! command -v jq &> /dev/null
then
    echo "jq is a dependency, and could not be found, see https://stedolan.github.io/jq for installation details"
    exit
fi

Help()
{
	echo "Usage: $0 -k <keyboard> -m <keymap> -c <convert_to controller> -r -h"
	echo ""
	echo "  -k keyboard directory (optional, default is all fingerpunch keyboards)"
	echo "  -m keymap (optional, defaults to the 'default' keymap)"
	echo "  -c add CONVERT_TO parameter for a controller (eg -c stemcell)"
	echo "  -r (optional, run the build command(s), defaults to outputting the build string)"
	echo "  -h (show this dialog)"
	echo ""
	echo "Examples: "
	echo "--------"
	echo "fp_build.sh -k \"rockon/v2\" -m sadekbaroudi -r"
	echo "fp_build.sh -m sadekbaroudi"
	echo "fp_build.sh -k \"barobord\""
}

get_valid_keyboards() {
	valid_keyboards=""
	directories=$(find ${1}/* -maxdepth 0 -type d)
	echo "${directories}" | while read line; do
		if [[ -e "${line}/fp_build.json" ]]; then
		    echo -n "${line} "
		fi
		for i in {1..9}
		do
			if [[ -e "${line}/v${i}/fp_build.json" ]]; then
			    echo -n "${line}/v${i} "
			fi
		done
	done
}

build_keyboard() {
	if [[ -z "${1}" ]]; then
		echo "build_keyboard: no first argument"
	fi
	if [[ -z "${2}" ]]; then
		echo "build_keyboard: no second argument"
	fi
	if [[ -z "${3}" ]]; then
		echo "build_keyboard: no third argument"
	fi
	if [[ -z "${4}" ]]; then
		echo "build_keyboard: no fourth argument"
	fi
	if [[ -z "${5}" ]]; then
		echo "build_keyboard: no fifth argument"
	fi

	build_json="${1}/fp_build.json"
	keyboard_base_dir="${1}"
	keyboard_name="${1#${2}/}"

	build_string="make ${keyboard_base_dir#keyboards\/}:${3}"
	echo "${build_string}"
	# get the total number of paramters
	top_level_element_count=$(cat "${build_json}" | jq 'length')
	for ((param_iter = 0 ; param_iter < top_level_element_count ; param_iter++)); do
		param_type=$(cat "${build_json}" | jq -r ".[${param_iter}].type")
		user_input_string=$(cat "${build_json}" | jq -r ".[${param_iter}].user_input")
		if [[ "${param_type}" == "one-of" ]]; then
			options_count=$(cat "${build_json}" | jq ".[${param_iter}].names | length")
			user_input_string+=" (0-${options_count}): "

			echo -n "${user_input_string}"
			read user_choice
			while [[ $user_choice -lt 0 || $user_choice -gt $options_count ]]; do
				echo "Invalid choice: ${user_choice}"
				echo -n "${user_input_string}"
				read user_choice
			done

			# start at 1, because 0 should always be "none"
			param_names_counter=1
			param_names=$(cat "${build_json}" | jq -r ".[${param_iter}].names | @sh" | tr -d \')
			for param_name in $param_names; do
			    if [[ $param_names_counter -eq $user_choice ]]; then
			    	build_string+=" ${param_name}=yes"
			    fi
			    ((param_names_counter+=1))
			done
		elif [[ "${param_type}" == "single" ]]; then
			user_input_string+=" (yes/no): "

			echo -n "${user_input_string}"
			read user_choice

			while [[ $user_choice != "yes" && $user_choice != "no" ]]; do
				echo "Invalid choice: ${user_choice}"
				echo -n "${user_input_string}"
				read user_choice
			done

			param_name=$(cat "${build_json}" | jq -r ".[${param_iter}].name")
			build_string+=" ${param_name}=${user_choice}"
		else
			echo "invalid type in json file: ${param_type}"
			exit
		fi
	done

	if [[ -n "${5}" && "${5}" != "no" ]]; then
		build_string+=" CONVERT_TO=${5}"
	fi

	echo ""
	echo "${build_string}"
	echo ""

	if [[ "${4}" == "yes" ]]; then
		echo "fp_build.sh: Running QMK Build...."
		echo ""
		eval "${build_string}"
	fi
}

Keyboard=""
Keymap="default"
RunBuild="no"
ConvertTo="no"
while getopts "k:m:c:rh" option; do
    case $option in
        k) Keyboard=${OPTARG};;
        m) Keymap=${OPTARG};;
		c) ConvertTo=${OPTARG};;
		r) RunBuild="yes";;
        h) Help
           exit;;
    esac
done

#### code starts here

# set up variables
FP_KB_DIR="keyboards/fingerpunch"
FP_KB=("${Keyboard}")
if [[ -z "${Keyboard}" ]]; then
	FP_KB=$(get_valid_keyboards "${FP_KB_DIR}")
else
	FP_KB=("${FP_KB_DIR}/${FP_KB}")
	if [[ ! -e "${FP_KB}" ]]; then
		echo "${FP_KB} is not a valid file, can't build"
		exit
	fi
fi;

for filename in $FP_KB; do
	echo "Running for ${filename}"
	build_keyboard "${filename}" "${FP_KB_DIR}" "${Keymap}" "${RunBuild}" "${ConvertTo}"
done