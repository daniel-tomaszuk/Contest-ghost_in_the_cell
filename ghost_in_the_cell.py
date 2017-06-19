import sys
import math



# classes
class Factory():
    def __init__(self, indx, units, prod):
        self.indx = indx
        self.units = units
        self.prod = prod


# # functions
# # check if index is in class list
# def is_in(index, class_list):
#     for obj in class_list:
#         if obj.indx == index:
#             return True
#     return False




factory_count = int(input())  # the number of factories
link_count = int(input())  # the number of links between factories
distances = [] # the distance between factories
for i in range(link_count):
    factory_1, factory_2, distance = [int(j) for j in input().split()]
    distances.append([factory_1, factory_2, distance])

turn_number = 0
bomb_counter = 5

# game loop
while True:
    # variables
    my_fac = []
    neutral_fac = []
    enemy_fac = []        
        
    entity_count = int(input())  # the number of entities (e.g. factories and troops)
    for i in range(entity_count):
        entity_id, entity_type, arg_1, arg_2, arg_3, arg_4, arg_5 = input().split()
        entity_id = int(entity_id)
        arg_1 = int(arg_1)
        arg_2 = int(arg_2)
        arg_3 = int(arg_3)
        arg_4 = int(arg_4)
        arg_5 = int(arg_5)    
    
    # factories
        if entity_type == 'FACTORY' and arg_1 == 1:
            my_fac.append(Factory(entity_id, arg_2, arg_3))
        elif entity_type == 'FACTORY' and arg_1 == 0:
            neutral_fac.append(Factory(entity_id, arg_2, arg_3))
        elif entity_type == 'FACTORY' and arg_1 == -1:
            enemy_fac.append(Factory(entity_id, arg_2, arg_3))

#############################################################
   
    # check nearest factories
    my_move = ''
    obj_counter = 0
    # for one my factory
    not_my_fac = neutral_fac + enemy_fac
    for obj in my_fac:        
        closest_fac_dist = 100
        closest_fac_id = -1
        # for one not my factory
        for not_my in not_my_fac:
            # for every distance search for nearest factory
            for dist_list in distances:                
                if (obj.indx in dist_list[0:2] 
                    and not_my.indx in dist_list[0:2]):
                    if closest_fac_dist > dist_list[2]:
                        closest_fac_dist = dist_list[2]
                        # check which one is the factory to go to
                        if obj.indx == dist_list[1]:
                            closest_fac_id = dist_list[0]
                        else: 
         
                            closest_fac_id = dist_list[1]
        obj_counter += 1                    
        if closest_fac_id != -1:
            my_move += 'MOVE {} {} {}'.format(str(obj.indx), 
                                              str(closest_fac_id), 
                                              str(5))        
            if len(my_fac) > 1 and obj_counter < len(my_fac):
                my_move += ';'


    # bombs
    closest_fac_dist = 100
    closest_fac_id = -1
    for obj in my_fac:
        # for one not my factory
        for enem_fac in enemy_fac:
            # for every distance search for nearest factory
            for dist_list in distances:                
                if (obj.indx in dist_list[0:2] 
                    and enem_fac.indx in dist_list[0:2]
                    and enem_fac.prod == 3):
                    if closest_fac_dist > dist_list[2]:
                        closest_fac_dist = dist_list[2]
                        # check which one is the factory to go to
                        if obj.indx == dist_list[1]:
                            closest_fac_id = dist_list[0]
                        else: 
                            closest_fac_id = dist_list[1]    
    
    if closest_fac_id != -1 and bomb_counter <= 0 and len(my_move) != 0:
        my_move += ';BOMB {} {}'.format(str(obj.indx), str(closest_fac_id))
        bomb_counter = 10


    # upgrades
    for obj in my_fac:
        if obj.units >= 10 and len(my_move) != 0:
            my_move += ';INC {}'.format(obj.indx)


    if len(my_move) == 0:
        my_move += 'MSG :)'

        
    # if turn_number < 3:
    print(my_move)
    # else:
    #     print('MSG', len(my_fac))
    
    turn_number += 1
    bomb_counter -= 1






    # Any valid action, such as "WAIT" or "MOVE source destination cyborgs"
    # print("WAIT")

