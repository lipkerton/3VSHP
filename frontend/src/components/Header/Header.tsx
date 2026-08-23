import mainLogo from "./assets/logo.png"
import simintechLogo from "./assets/logo-1.png"
import simintechLogoHover from "./assets/logo-1h.png"
import dassaultLogo from "./assets/logo-2.png"
import dassaultLogoHover from "./assets/logo-2h.png"
import lcmsLogo from "./assets/logo-3.png"
import lcmsLogoHover from "./assets/logo-3h.png"

type NavigationItem = {
	href: string;
	logo: string;
	hover: string;
	alt: string;
}

const navigationItems: NavigationItem[] = [
	{
		href: "#simintech",
		logo: simintechLogo,
		hover: simintechLogoHover,
		alt: "simintech",
	},
	{
		href: "#bsexalead",
		logo: dassaultLogo,
		hover: dassaultLogoHover,
		alt: "bsexalead",
	},
	{
		href: "#lcms",
		logo: lcmsLogo,
		hover: lcmsLogoHover,
		alt: "lcms",
	}
]

function Header() {
	return(
		<header>
			<a href="#main">
				<img src={mainLogo} alt="3VServices" />
			</a>
				<nav aria-label="Основная навигация">
					<ul>
						{
							navigationItems.map((navigationItem) => (
								<li>
									<a href={navigationItem.href}>
										<img src={navigationItem.logo} alt={navigationItem.alt} />
										<img src={navigationItem.hover} alt="" />
									</a>
								</li>
							))
						}
					</ul>
				</nav>
		</header>
	);
}

export default Header;