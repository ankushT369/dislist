/* 
 * Enum contains all the instructions 
 * which come from the server-side
 *
 */

#[repr(i32)]
#[derive(Copy, Clone)]
#[derive(Debug)]
pub enum Status {
    Success = 200,
    InvalidSyntaxCommandTraverse = 111,
    InvalidSyntaxCommandInsert = 112,
    InvalidSyntaxCommandRemove = 113,
    UnknownCommand = 101,
    OutOfRange = 102,
    Failure = 404,
}

#[derive(Debug)]
#[derive(PartialEq)]
pub enum Instruction {
    INSERT,
    REMOVE,
    TRAVERSE,
    INVALID,
}


/* 
 * InstructionInfo contains information about
 * the parsed information
 */
#[derive(Debug)]
pub struct InstructionInfo {
   pub ins_type: Instruction,
   pub has_value: bool,
   pub value: Option<i32>,
}

pub fn parse(data: &str) -> Result<InstructionInfo, Status> {
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
                    return Ok(instance);
                } else {
                    println!("Invalid number: {}", parts[0]);
                    return Err(Status::InvalidSyntaxCommandInsert);
                }
            } else {
                return Err(Status::InvalidSyntaxCommandInsert);
            }
        } else {
            return Err(Status::InvalidSyntaxCommandInsert);
        }
    } else if instruction == "REMOVE" {
        let length = instruction.len();

        if length == 6 {
            instance.ins_type = Instruction::REMOVE;
            instance.has_value = false;
            instance.value = None;
            return Ok(instance);
        } else {
            return Err(Status::InvalidSyntaxCommandRemove);
        }
    } else {
        let instruction = &data[0..8];
        let length = instruction.len();

        if instruction == "TRAVERSE" {
            if length == 8 {
                instance.ins_type = Instruction::TRAVERSE;
                instance.has_value = false;
                instance.value = None;
                return Ok(instance);
            } else {
                return Err(Status::InvalidSyntaxCommandTraverse);
            }
        } else {
            return Err(Status::UnknownCommand);
        }
    }
}
