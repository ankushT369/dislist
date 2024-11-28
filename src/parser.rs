
/* 
 * Enum contains all the instructions 
 * which come from the server-side
 *
 */


enum Instruction {
    INSERT,
    REMOVE,
    TRAVERSE,
    INVALID,
}

/* InstructionInfo contains information about
 * the parsed information
 */
pub struct InstructionInfo {
    ins_type: Instruction,
    has_value: bool,
    value: Option<i32>,
}

pub fn parse(data: &str) -> InstructionInfo {
    let instruction = &data[0..6];
    let length = data.len();

    let mut instance = InstructionInfo {
        ins_type: Instruction::INVALID,
        has_value: false,
        value: None,
    };


    if instruction == "INSERT" {
        if length >= 8 {
            let remaining = data.get(7..).unwrap_or("").trim_matches('\0');
            let parts: Vec<&str> = remaining.split_whitespace().collect();

            if parts.len() == 1 {
                if let Ok(num) = parts[0].parse::<i32>() {
                    instance.ins_type = Instruction::INSERT;
                    instance.has_value = true;
                    instance.value = Some(num);

                    println!("Valid command: INSERT {}", num);
                } else {
                    println!("Invalid number: {}", parts[0]);
                }
            } else {

            }
        } else {

        }
    } else if instruction == "REMOVE" {
        if length == 6 {
            instance.ins_type = Instruction::REMOVE;
            instance.has_value = false;
            instance.value = None;            

        } else {

        }
    } else {
        let instruction = &data[0..8];

        if instruction == "TRAVERSE" {
            if length == 8 {
                instance.ins_type = Instruction::TRAVERSE;
                instance.has_value = false;
                instance.value = None;

            } else {

            }
        } else {
            println!("Its unknown");
        }
    }

    instance
}

