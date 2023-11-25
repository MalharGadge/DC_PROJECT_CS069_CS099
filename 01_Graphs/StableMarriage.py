import random
from statistics import mean
import timeit

class Person:
    def __init__(self, gender, name, is_available, preference_list):
        self.gender = gender
        self.name = name
        self.is_available = is_available
        self.preference_list = preference_list
        self.proposed_by = []

    def __repr__(self):
        return self.name

    def print_person(self):
        pass

class Pairing:
    def __init__(self, guy, girl):
        self.guy = guy
        self.girl = girl

    def __repr__(self):
        return "({}, {})".format(self.guy.name, self.girl.name)

class Community:
    def __init__(self, num_gender):
        self.num_gender = num_gender
        self.guys = {}
        self.girls = {}

        guy_names = [f"Guy{i}" for i in range(1, num_gender + 1)]
        girl_names = [f"Girl{i}" for i in range(1, num_gender + 1)]

        for guy_name in guy_names:
            sc_girls = girl_names[:]
            random.shuffle(sc_girls)
            self.guys[guy_name] = Person('M', guy_name, True, sc_girls)

        for girl_name in girl_names:
            sc_guys = guy_names[:]
            random.shuffle(sc_guys)
            self.girls[girl_name] = Person('F', girl_name, True, sc_guys)

        self.pairs = {}
        self.is_everyone_paired = False
        self.iterations = 0

    def get_first_available_guy(self):
        for guy_name in self.guys.keys():
            if self.guys[guy_name].is_available:
                return guy_name
        return None

    def run_stable_marriage_algorithm(self):
        def algorithm_wrapper():
            available_guy_name = self.get_first_available_guy()
            while available_guy_name is not None:
                available_guy = self.guys[available_guy_name]
                proposed_girl = None

                for preference in available_guy.preference_list:
                    if available_guy_name not in self.girls[preference].proposed_by:
                        proposed_girl = self.girls[preference]
                        proposed_girl.proposed_by.append(available_guy_name)
                        break

                if proposed_girl.is_available:
                    proposed_girl.is_available = False
                    available_guy.is_available = False
                    self.pairs[proposed_girl.name] = Pairing(available_guy, proposed_girl)
                else:
                    other_guy = self.pairs[proposed_girl.name].guy
                    proposed_girl_preference = proposed_girl.preference_list
                    if proposed_girl_preference.index(available_guy_name) < proposed_girl_preference.index(other_guy.name):
                        other_guy.is_available = True
                        available_guy.is_available = False
                        self.pairs[proposed_girl.name] = Pairing(available_guy, proposed_girl)

                available_guy_name = self.get_first_available_guy()
                self.iterations += 1

            self.is_everyone_paired = True

        execution_time = timeit.timeit(algorithm_wrapper, number=1)
        print(f"Total execution time: {execution_time:.6f} seconds")

        # Print statistics after running the algorithm
        self.stats()

    def get_average_index(self):
        preference_indices_male = []
        preference_indices_female = []
        for pair in self.pairs:
            guy = self.pairs[pair].guy
            girl = self.pairs[pair].girl
            preference_indices_male.append(guy.preference_list.index(girl.name) + 1)
            preference_indices_female.append(girl.preference_list.index(guy.name) + 1)

        average_male_index = mean(preference_indices_male)
        average_female_index = mean(preference_indices_female)

        return average_male_index, average_female_index

    def stats(self):
        if not self.is_everyone_paired:
            print("Run the run_stable_marriage_algorithm first!")
        else:
            print("STATS:")
            print("This stable marriage solution took {} iterations to complete.".format(self.iterations))
            male_index, female_index = self.get_average_index()
            print("In each pairing, the average girl ranking for a guy was {}.".format(male_index))
            print("In each pairing, the average guy ranking for a girl was {}.".format(female_index))

            if female_index > male_index:
                index_difference = female_index - male_index
                print("Therefore on average, guys got {} preference ranks higher than the girls."
                      .format(index_difference))
            else:
                index_difference = male_index - female_index
                print("Therefore on average, girls got {} preference ranks higher than the guys."
                      .format(index_difference))

            print("Based on the population of the community, this is {}% better"
                  .format(index_difference * 100 / float(self.num_gender - 1)))

def main():
    com = Community(10)
    com.run_stable_marriage_algorithm()

if __name__ == '__main__':
    main()
