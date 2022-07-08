# Tic Tac Toe
import random
player_1 = 1
player_2 = 2
player_cpu = 3
tie = 1
win_1 = 2
win_2 = 3
row = 3
column = 3


def main_menu():
    print("TicTacToe")
    print("1.) Player vs Player Mode")
    print("2.) Player vs Cpu Mode")
    print("Quit")
    loop = 1
    while loop != 0:
        game_mode = input("Select Mode: ")
        if game_mode == 1:
            pvp()
        elif game_mode == 2:
            cpu()
        elif game_mode == 3:
            print("Thank You For Playing")
            loop = 0
        else:
            print("Please Enter A Valid Mode")


def pvp():
    print("Player Vs Player Selected")
    active = True
    current_player = player_1
    current_board = init_board(column, row)
    print_board(current_board)
    victory = False
    tie = False
    while active:
        input1 = input("Please Enter Position Row followed By Column")
        input2 = input("")
        if input1 <= 2 and input2 <= 2 and input1 >= 0 and input2>=0:
            if current_board[input1][input2] == -1:
                victory = is_victory(current_board,current_player)
                tie = is_tie(current_board)
                if victory:
                    print("You Have Won")
                    active = False
                elif tie:
                    print("It is a Tie")
                    active = False
                else:
                    print_board(current_board)
                    current_player = switch_player(current_player)
            else:
                print("Position Already Taken Please Choose Another")
        else:
            print ("Please Enter Valid Selection")


def cpu():
    print("Playing against cpu")
    active = True
    current_player = player_1
    victory= False
    tie = False
    current_board = init_board(row,column)
    while active:
        if current_player == player_1:
            print("Please Enter Row Followed by column")
            input_1 = input()
            input_2 = input()
            if check_input(input_1, input_2, current_board):
                current_board[input_1][input_2]= current_player
                victory = is_victory(current_board,current_player)
                tie = is_tie(current_board)
                if victory:
                    print("You Have Won")
                    active = False
                elif tie:
                    print ("It is a Tie")
                    active = False
                current_player = switch_player(current_player)
            else:
                print("Please Enter Valid Selection")

        if current_player == player_2:
            input_1 = random.randint(0,2)
            input_2 = random.randint(0,2)
            if check_input(input_1, input_2, current_board):
                current_board[input_1][input_2]= current_player
                victory = is_victory(current_board,current_player)
                tie = is_tie(current_board)
                if victory:
                    print("Cpu has Won")
                    active = False
                if tie:
                    print ("It is a Tie")
                    active = False
                print_board(current_board)
                current_player = switch_player(current_player)
def check_input(input1,input2,board):
    if input1 <= 2 and input2 <= 2 and input1>=0 and input2>=0:
        if board[input1][input2] != -1:
            return False
        else:
            return True

    else:
        return False

    return True
def is_victory( board, current_player):
    #todo fix Ugly Ugly Spaghetti Code
    if board[0][0] == current_player and board[0][1] == current_player and board[0][2] == current_player:
        return True
    elif board[1][0] == current_player and board[1][1] == current_player and board[1][2] == current_player:
        return True
    elif board[2][0] == current_player and board[2][1] == current_player and board[2][2] == current_player:
        return True
    elif board[0][0] == current_player and board[1][0] == current_player and board[2][0] == current_player:
        return True
    elif board[1][0] == current_player and board[1][1] == current_player and board[2][1] == current_player:
        return True
    elif board[2][0] == current_player and board[2][1] == current_player and board[2][2] == current_player:
        return True
    elif board[0][0] == current_player and board[1][1] == current_player and board[2][2] == current_player:
        return True
    elif board[2][0] == current_player and board[1][1] == current_player and board[2][0] == current_player:
        return True
    else:
        return False


def is_tie(board):
    for r in range(len(board)):
        for col in range(len(board[r])):
            if board[r][col] == -1:
                return False
    return True


def init_board(r, col):
    board = [[-1 for x in range(r)] for y in range(col)]
    return board


def print_board(board):
    r = 0
    col = 0
    for r in range(len(board)):
        for col in range(len(board[r])):
            print_symbol(board[r][col])
            if col != column - 1:
                print '|',
            else:
                print
        if r != row - 1:
            print("---------")


def print_symbol(place_maker):
    if place_maker == player_1:
        print 'X',
    elif place_maker == player_2:
        print'O',
    else:
        print ' ',


def switch_player(current_player):
    if current_player == player_1:
        return player_2
    elif current_player == player_2:
        return player_1


if __name__ == '__main__':
    main_menu()
